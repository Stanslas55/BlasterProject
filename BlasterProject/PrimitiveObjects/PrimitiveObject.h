#pragma once
#include <vector>

#include "../Vector3/Vector3.hpp"
#include "Ray.hpp"

class PrimitiveObject {   

	protected:	

    public:

        /**
         *  \fn     intersect
         *  \brief  This function returns the intersection points for a given radius.
         *
         *  \param[in]      pRay                    The Ray we're searching the intersections with the PrimitiveObject.
         *  \return         std::vector<Vector3>    Vector containing the intersection points.
         */
		virtual std::vector<Vector3> intersect(const Ray& pRay) const = 0;

        // Add a material.
        // Add a Transfrom.
};