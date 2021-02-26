#pragma once

#include "../LightSource.hpp"
#include "Vector3/Vector3.hpp"

class DirectionalLight : public LightSource {

private:

	Vector3 m_direction;

	/**
	 * \fn      DirectionalLight
	 * \brief   Default constructor.
	 */
	DirectionalLight();

public:

	/**
	 * \fn      DirectionalLight
	 * \brief   Recommended constructor.
	 *
	 * \param[in]   pPosition
	 * \param[in]   pColor
	 */
	DirectionalLight(Vector3 pDirection, RGBQUAD pColor = { 255, 255, 255 });

	inline const Vector3& direction() const { return m_direction; }
	inline Vector3& direction() { return m_direction; }
};