#pragma once

#include "../Vector3/Vector3.hpp" 
#include "Material/Material.hpp"

class Collision {

private:

	Vector3 m_point;
	Material m_material;
	Vector3 m_normal;
	bool m_collided;

public:

	static const Collision noCollision;

	/**
	 * \fn      Collision
	 * \brief	Collision constructor.
	 * 
	 * \param[in]   pPoint
	 * \param[in]   m_normal
	 */
	Collision(const Vector3& pPoint, const Material& pMaterial = Material::defaultMaterial, const Vector3& m_normal = Vector3::zero, const bool pCollided = false);

	/**
	 * \fn      Collision
	 * \brief   Copy Constructor.
	 * 
	 * \param[in]   pSrc
	 */
	Collision(const Collision& pSrc);

	inline const Vector3& point() const { return m_point; }
	inline const Material& material() const { return m_material; }
	inline const Vector3& normal() const { return m_normal; }
	inline const bool collided() const { return m_collided; }

	Collision& operator=(const Collision& pSrc);
};

/**
 * \fn      operator<<
 * \brief   Write a collision to a output stream.
 *
 * \param[in]   pFlux
 * \param[in]   pC
 * \return      std::ostream&
 */
std::ostream& operator<<(std::ostream& pFlux, const Collision& pC);