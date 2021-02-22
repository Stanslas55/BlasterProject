#pragma once
#include <vector>

#include "../Vector3/Vector3.hpp"
#include "Ray.hpp"
#include "Material/material.hpp"
#include "Collision.hpp"

class PrimitiveObject {   

protected:	

    Material m_material;

public:

    PrimitiveObject(const Material& pMaterial);

    inline const Material& material() const { return m_material; }
    inline Material& material() { return m_material; }

	/**
	 *  \fn     intersect
	 *  \brief  This function returns the intersection points for a given ray.
	 *
	 *  \param[in]      pRay				The Ray we're searching the intersections with the PrimitiveObject.
	 *  \return         const Collision		Collision with pRay.origin() as point if there is no intersection.
	 */
	virtual const Collision intersect(const Ray& pRay) const = 0;

    // Add a material.
    // Add a Transfrom.
};