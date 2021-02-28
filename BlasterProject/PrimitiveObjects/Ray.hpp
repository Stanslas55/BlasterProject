#pragma once
#include "../Vector3/Vector3.hpp"

class Ray {

private:
	Vector3 m_origin;
	Vector3 m_end;		
	Vector3 m_direction;

public:
	inline Vector3& origin() { return m_origin; }
	inline Vector3& end() { return m_end; }
	inline Vector3& direction() { return m_direction; }

	inline const Vector3& origin() const { return m_origin; }
	inline const Vector3& end() const { return m_end; }
	inline const Vector3& direction() const { return m_direction; }

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
	Vector3 point(double pT) const { return m_origin + m_direction * pT; }

	void print(std::ostream& pFlux) const;
};
std::ostream& operator<<(std::ostream& pFlux, const Ray& pRay);