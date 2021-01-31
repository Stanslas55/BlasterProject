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

		inline const Vector3& gOrigin() const { return origin; }
		inline const Vector3& gEnd() const { return end; }
		inline const Vector3& gDirection() const { return direction; }

		Ray();
		Ray(const Vector3& pOrigin, const Vector3& pDirection);	
		static Ray fromLine(const Vector3& pOrigin, const Vector3& pEnd);
		/**
		 *  \fn     point
		 *  \brief  Calculates the coordinate of a point according to pT step: origin + direction * pT
		 *
		 *  \param[in]      pT              The step to apply.				
		 *  \return         Vector3			Returns the calculated point.
		 */
		Vector3 point(double pT) const { return origin + direction * pT; }
		void print(std::ostream& pFlux);
};
std::ostream& operator<<(std::ostream& pFlux, Ray pRay);