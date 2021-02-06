#include "Ray.hpp"

Ray::Ray() {
	m_origin = Vector3(0, 0, 0);
	m_end = Vector3(0, 0, 0);
	m_direction = Vector3(0, 0, 0);
}

Ray::Ray(const Vector3& pOrigin, const Vector3& pDirection) {	
	m_origin = pOrigin;
	m_end = Vector3(0, 0, 0);
	m_direction = pDirection;
}

Ray Ray::fromLine(const Vector3& pOrigin, const Vector3& pEnd) {
	Ray ray;
	Vector3 substraction = pEnd - pOrigin;

	ray.m_origin = pOrigin;
	ray.m_end = pEnd;
	ray.m_direction = Vector3::normalize(substraction);
	return ray;
}

void Ray::print(std::ostream& pFlux) const {
	pFlux << "Ray: {Origin: " << m_origin << ", Direction: " << m_direction << "}";
}

std::ostream& operator<<(std::ostream& pFlux, const Ray& pRay) {
	pRay.print(pFlux);
	return pFlux;
}