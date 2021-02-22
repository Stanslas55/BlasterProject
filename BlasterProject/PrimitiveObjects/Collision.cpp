#include "Collision.hpp"

const Collision Collision::noCollision = Collision(Vector3::zero);

Collision::Collision(const Vector3& pPoint, const Material& pMaterial, const Vector3& pNormal, const bool pCollided) : m_point(pPoint), m_material(pMaterial), m_normal(pNormal), m_collided(pCollided) {}

Collision::Collision(const Collision& pSrc) : m_point(pSrc.m_point), m_material(pSrc.m_material), m_normal(pSrc.m_normal), m_collided(pSrc.m_collided) {}

Collision& Collision::operator=(const Collision& pSrc) {

	if (this == &pSrc)
		return *this;

	m_point = pSrc.m_point;
	m_material = pSrc.m_material;
	m_normal = pSrc.m_normal;
	m_collided = pSrc.m_collided;

	return *this;
}

std::ostream& operator<<(std::ostream& pFlux, const Collision& pC) {
	if (pC.collided())
		pFlux << "Collision point : " << pC.point() << std::endl << "Material" << pC.material() << std::endl << "Collision normal: " << pC.normal();
	else
		pFlux << "Collision : no Collision";

	return pFlux;
}