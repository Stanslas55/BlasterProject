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

void Scene::takePictureNaive(FIBITMAP** pImage) {

	int w = m_camera.m_width, h = m_camera.m_height;

	*pImage = FreeImage_Allocate(w, h, 32);

	int i, j;

	double offset = m_camera.m_offset;
	double offsetd2 = offset / 2.0;
	double xLeft = m_camera.m_corners[0].x() + offsetd2;

	Vector3 curPosition(m_camera.m_corners[0] + Vector3(offsetd2, offsetd2, 0.0));
	Vector3 camOrigin = m_camera.m_position;

	int wh = w * h;

	RGBQUAD black = { 0, 0, 0, 0 };
	RGBQUAD white = { 255, 255, 255, 255 };

	int nbObjs = m_objects.size();

#pragma omp parallel for
	for (i = 0; i < wh; i++) {

		const int x = i % w;
		const int y = int(ceil(double(i) / double(w)));

		const Vector3 pos = curPosition + Vector3(x * offset, -y * offset, 0.0);

		const Ray r = Ray::fromLine(camOrigin, pos);

		std::vector<Vector3> its;
		bool setWhite = false;

		for (int k = 0; k < nbObjs; k++) {
			if (!m_objects[k]->intersect(r).empty()) {
				setWhite = true;
				break;
			}
		}

		if (setWhite) {
			FreeImage_SetPixelColor(*pImage, x, y, &white);
		} else {
			FreeImage_SetPixelColor(*pImage, x, y, &black);
		}
	}

	/*for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			curPosition.x() += offset;

			Ray r = Ray::fromLine(camOrigin, curPosition);

			std::vector<Vector3> intersections;

			double nbObjs = m_objects.size();

			for (size_t k = 0; k < nbObjs; k++) {
				std::vector<Vector3> its = m_objects[k]->intersect(r);
				intersections.insert(intersections.end(), its.begin(), its.end());
			}

			if (intersections.empty()) {
				FreeImage_SetPixelColor(*pImage, j, i, &black);
			} else {
				FreeImage_SetPixelColor(*pImage, j, i, &white);
			}
		}

		curPosition.x() = xLeft;
		curPosition.y() -= offset;
	}*/
}