#pragma once

#include "../LightSource.hpp"
#include "../../Vector3/Vector3.hpp"

class PointLight : public LightSource {

private:

	Vector3 m_position;

	/**
	 * \fn      PointLight
	 * \brief   Default constructor.
	 */
	PointLight();

public:
	
	/**
	 * \fn      PointLight
	 * \brief   Recommended constructor.
	 * 
	 * \param[in]   pPosition
	 * \param[in]   pColor
	 */
	PointLight(Vector3 pPosition, RGBQUAD pColor = { 255, 255, 255, 255 });

	inline const Vector3& position() const { return m_position; }
	inline Vector3& position() { return m_position; }

};