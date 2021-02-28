#include "Ray.hpp"

Ray::Ray() {
	m_origin = Vector3::zero;
	m_direction = Vector3::zero;
}

Ray::Ray(const Vector3& pOrigin, const Vector3& pDirection) {	
	m_origin = pOrigin;
	m_direction = pDirection;
}

Ray Ray::fromLine(const Vector3& pOrigin, const Vector3& pEnd) {
	return Ray(pOrigin, Vector3::normalize(pEnd - pOrigin));
}

void Ray::print(std::ostream& pFlux) const {
	pFlux << "Ray: {Origin: " << m_origin << ", Direction: " << m_direction << "}";
}

std::ostream& operator<<(std::ostream& pFlux, const Ray& pRay) {
	pRay.print(pFlux);
	return pFlux;
}