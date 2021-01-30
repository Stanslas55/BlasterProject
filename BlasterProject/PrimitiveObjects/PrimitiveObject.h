#pragma once
#include <vector>

#include "../Vector3/Vector3.hpp"
#include "Ray.hpp"

class PrimitiveObject {
	protected:		
          /**
         *  \fn     intersect
         *  \brief  This function returns the intersection points for a given radius.
         *
         *  \param[in]      pRay            The Ray we're searching the intersections with the PrimitiveObject.
         *  \return         std::vector<Vector3>    vector containing the intersection points.
         */
		virtual std::vector<Vector3> intersect(Ray pRay) = 0;
};