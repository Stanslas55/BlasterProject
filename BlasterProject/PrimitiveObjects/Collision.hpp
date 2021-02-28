#pragma once

class PrimitiveObject;

#include "Vector3/Vector3.hpp" 
#include "Material/Material.hpp"
#include "PrimitiveObject.h"


class Collision {

private:

	bool m_collided;
	PrimitiveObject* m_object;
	Vector3 m_point;
	Vector3 m_normal;
	double m_dist;
	Vector3 m_directionToOrigin;

public:

	static const Collision noCollision;		/*< No collision object. */

	/**
	 * \fn      Collision
	 * \brief	Collision constructor.
	 * 
	 * \param[in]   pPoint
	 * \param[in]   m_normal
	 * \param[in]   pDirectionToOrigin
	 * \param[in]   pCollided
	 */
	Collision(const Vector3& pPoint = Vector3::zero, const Vector3& m_normal = Vector3::zero, const Vector3& pDirectionToOrigin = Vector3::zero, const bool pCollided = true);

	/**
	 * \fn      Collision
	 * \brief   Copy Constructor.
	 * 
	 * \param[in]   pSrc
	 */
	Collision(const Collision& pSrc);

	inline PrimitiveObject* object() const { return m_object; }
	inline void object(PrimitiveObject* pObject) { m_object = pObject; }
	inline const Vector3& point() const { return m_point; }
	inline const Vector3& normal() const { return m_normal; }
	inline const double& distance() const { return m_dist; }
	inline double& distance() { return m_dist; }
	inline const bool collided() const { return m_collided; }
	inline const Vector3& directionToOrigin() const { return m_directionToOrigin; }

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