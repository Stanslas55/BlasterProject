#pragma once
#include "../Vector3/Vector3.hpp"

class Ray {
	private:
		Vector3 origin;
		Vector3 end;		
		Vector3 direction;

	public:
		inline Vector3& gOrigin() { return origin; }
		inline Vector3& gEnd() { return end; }
		inline Vector3& gDirection() { return direction; }

		Ray();
		Ray(Vector3 pOrigin, Vector3 pEnd);
		/**
		 *  \fn     point
		 *  \brief  Calculates the coordinate of a point according to pT step: origin + direction * pT
		 *
		 *  \param[in]      pT              The step to apply.				
		 *  \return         Vector3			Returns the calculated point.
		 */
		Vector3 point(double pT) const { return origin + direction * pT; }
};

