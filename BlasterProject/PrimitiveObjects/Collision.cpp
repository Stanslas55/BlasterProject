#include "Collision.hpp"

const Collision Collision::noCollision = Collision(Vector3::zero, Vector3::zero, Vector3::zero, false);

Collision::Collision(const Vector3& pPoint, const Vector3& pNormal, const Vector3& pDirectionToOrigin, const bool pCollided) : m_collided(pCollided), m_point(pPoint), m_normal(pNormal), m_directionToOrigin(pDirectionToOrigin), m_object(nullptr) {}

Collision::Collision(const Collision& pSrc) : m_collided(pSrc.m_collided), m_object(pSrc.m_object), m_point(pSrc.m_point), m_normal(pSrc.m_normal) {}

Collision& Collision::operator=(const Collision& pSrc) {

	if (this == &pSrc)
		return *this;

	m_collided = pSrc.m_collided;
	m_object = pSrc.m_object;
	m_point = pSrc.m_point;
	m_normal = pSrc.m_normal;

	return *this;
}

std::ostream& operator<<(std::ostream& pFlux, const Collision& pC) {
	if (pC.collided())
		pFlux << "Object " << pC.object() << std::endl << "Collision point : " << pC.point() << std::endl << "Collision normal: " << pC.normal();
	else
		pFlux << "Collision : no Collision";

	return pFlux;
}