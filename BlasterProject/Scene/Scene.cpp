#include "Scene.hpp"

Scene::Scene() {
	m_camera = Camera();

	m_objects = std::vector<std::shared_ptr<PrimitiveObject>>();
	m_lightSources = std::vector<std::shared_ptr<LightSource>>();
}

Scene::Scene(const Scene& pCopy) {
	m_camera = pCopy.m_camera;

	// TODO deep copy

	m_objects = pCopy.m_objects;
	m_lightSources = pCopy.m_lightSources;
}

Scene::Scene(const Camera& pCamera) {
	m_camera = pCamera;

	m_objects = std::vector<std::shared_ptr<PrimitiveObject>>();
	m_lightSources = std::vector<std::shared_ptr<LightSource>>();
}

void Scene::addPrimitive(PrimitiveObject* pPrimitive) {
	std::shared_ptr<PrimitiveObject> ptr_obj(pPrimitive);
	m_objects.push_back(std::move(ptr_obj));
}

void Scene::addLightSource(LightSource* pLightSource) {
	std::shared_ptr<LightSource> ptr_obj(pLightSource);
	m_lightSources.push_back(std::move(ptr_obj));
}

void Scene::addModel(Model* pModel) {
	std::shared_ptr<Model> ptr_obj(pModel);
	m_models.push_back(std::move(ptr_obj));
}


void Scene::takePictureNaive(FIBITMAP** pImage) {

	int w = m_camera.m_width, h = m_camera.m_height;

	*pImage = FreeImage_Allocate(w, h, 32);

	int i;

	double offset = m_camera.m_offset;
	double offsetd2 = offset / 2.0;
	double xLeft = m_camera.m_corners[0].x() + offsetd2;

	Vector3 curPosition(m_camera.m_corners[0] + Vector3(offsetd2, offsetd2, 0.0));
	const Vector3& camOrigin = m_camera.m_position;

	int wh = w * h;

#pragma omp parallel for
	for (i = 0; i < wh; i++) {

		const int x = i % w;
		const int y = i / w;

		const Vector3 pos = curPosition + Vector3(x * offset, -y * offset, 0.0);

		const Ray r = Ray::fromLine(camOrigin, pos);

		RGBQUAD color = getPixelColor(r);
		FreeImage_SetPixelColor(*pImage, x, y, &color);
	}
}

const Collision Scene::getClosestIntersectionNaive(const Ray& pRay, bool pEarlyStop) const {

	Collision closestCollision = Collision::noCollision;
	double sqDist = -1.0;
	double minSqDist = -1.0;

	for (const std::shared_ptr<PrimitiveObject>& obj : m_objects) {
		const Collision curCollision = obj->intersect(pRay);

		if (curCollision.collided()) {
			if (closestCollision.collided()) {
				sqDist = Vector3::sqDdistance(curCollision.point(), pRay.origin());

				if (sqDist < minSqDist) {
					closestCollision = curCollision;
					closestCollision.object(obj.get());
					minSqDist = sqDist;
				}
			}
			else {
				if (pEarlyStop)
					return curCollision;
				closestCollision = curCollision;
				closestCollision.object(obj.get());
				minSqDist = Vector3::sqDdistance(closestCollision.point(), pRay.origin());
			}
		}
	}

	if (closestCollision.collided())
		closestCollision.distance() = sqrt(minSqDist);
	return closestCollision;
}

RGBQUAD Scene::getPixelColor(const Ray& pRay, int pDepth) {

	int nbLightSources = m_lightSources.size();

	if (nbLightSources == 0)
		return m_camera.m_backgroundColor;

	/**
	 * Find closest instersection point
	 */

	return getPixelColor(getClosestIntersectionNaive(pRay), pDepth);
}

RGBQUAD Scene::getPixelColor(const Collision& pCollsision, int pDepth) {

	if (!pCollsision.collided()) {
		// No collision. Return background color.
		return m_camera.m_backgroundColor;
	}

	Ray secondaryRay;

	std::shared_ptr<PointLight> pointLight = nullptr;
	std::shared_ptr<DirectionalLight> directionalLight = nullptr;

	const Vector3& point = pCollsision.point();
	const Vector3& normal = pCollsision.normal();
	const Material& material = pCollsision.object()->material();
	const double distance = pCollsision.distance();

	RGBQUAD color = material.color();

	const Vector3& L = pCollsision.directionToOrigin();
	const Vector3& I = -L;

	Vector3 Ia = Vector3(color.rgbRed, color.rgbGreen, color.rgbBlue);
	Vector3 Id = Vector3::zero;
	Vector3 Is = Vector3::zero;

	/*if (pDepth > 1) {
		const Collision reflectionCollision = getClosestIntersectionNaive(Ray(point, I - normal * 2 * (I * normal)));

		if (reflectionCollision.collided()) {
			color = getPixelColor(reflectionCollision, pDepth - 1);
			Ia += Vector3(color.rgbRed, color.rgbGreen, color.rgbBlue);
		}
	}*/

	Ia *= material.ka();

	for (std::shared_ptr<LightSource> ls : m_lightSources) {

		if (ls->type() == LightSourceType::POINT) {
			pointLight = std::static_pointer_cast<PointLight>(ls);
			secondaryRay = Ray::fromLine(pCollsision.point(), pointLight->position());
		}
		else if (ls->type() == LightSourceType::DIRECTIONAL) {
			directionalLight = std::static_pointer_cast<DirectionalLight>(ls);
			secondaryRay = Ray(pCollsision.point(), directionalLight->direction());
		}
		else
			continue;

		const Collision collision = getClosestIntersectionNaive(secondaryRay, true);

		if (collision.collided())
			continue;

		if (ls->type() == LightSourceType::POINT) {
			pointLight->fAtt().precomputeCoeff(distance);
		} else if (ls->type() == LightSourceType::DIRECTIONAL) {
			directionalLight->fAtt().precomputeCoeff();
		}

		if (material.kd() != 0)
			Id += ls->fAtt().fAtt(ls->intensity() * (normal * secondaryRay.direction()));

		if (material.ks() != 0 || material.ke() != 0)
			Is += ls->fAtt().fAtt(ls->intensity() * pow(normal * Vector3::normalize(secondaryRay.direction() + L), material.ke()));
	}
	
	Id *= material.kd();
	Is *= material.ks();

	return {
		(BYTE)std::max(std::min(int(std::floor(Ia.x() + Id.x() + Is.x())), 255), 0),		// R
		(BYTE)std::max(std::min(int(std::floor(Ia.y() + Id.y() + Is.y())), 255), 0),		// G
		(BYTE)std::max(std::min(int(std::floor(Ia.z() + Id.z() + Is.z())), 255), 0),		// B
		255
	};
}

Collision* Scene::getCollisionArray() {
	
	int i;
	int w = m_camera.m_width, h = m_camera.m_height;
	int wh = w * h;

	Collision* collisions = new Collision[wh];

	double offset = m_camera.m_offset;
	double offsetd2 = offset / 2.0;
	double xLeft = m_camera.m_corners[0].x() + offsetd2;

	Vector3 curPosition(m_camera.m_corners[0] + Vector3(offsetd2, offsetd2, 0.0));
	const Vector3& camOrigin = m_camera.m_position;

#pragma omp parallel for
	for (i = 0; i < wh; i++) {

		const int x = i % w;
		const int y = i / w;

		const Vector3 pos = curPosition + Vector3(x * offset, -y * offset, 0.0);

		const Ray r = Ray::fromLine(camOrigin, pos);

		collisions[i] = getClosestIntersectionNaive(r);
	}

	return collisions;
}

Ray* Scene::getRayArray() {

	int w = m_camera.width(), h = m_camera.height();
	int wh = w * h;

	Ray* rays = new Ray[wh];

	double offset = m_camera.m_offset;
	double offsetd2 = offset / 2.0;

	Vector3 curPosition(m_camera.m_corners[0] + Vector3(offsetd2, offsetd2, 0.0));
	const Vector3& camOrigin = m_camera.m_position;

	int i;
#pragma omp parallel for
	for (i = 0; i < wh; i++) {
		const int x = i % w;
		const int y = i / w;

		const Vector3 pos = curPosition + Vector3(x * offset, -y * offset, 0.0);

		rays[i] = Ray::fromLine(camOrigin, pos);
	}

	return rays;
}
