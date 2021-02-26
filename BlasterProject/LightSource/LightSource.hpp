#pragma once

#include "FreeImage.h"
#include "Vector3/Vector3.hpp"

enum class LightSourceType {
	POINT,
	DIRECTIONAL,

	NONE
};

/**
 * \class	LightSource
 * \brief	Base light source class
 */
class LightSource {

protected:

	static int currentId;				/*< Counter of current light ID. Each LightSource has a unique ID. */

	int m_lightID;						/*< This light's Identifier. */
	//RGBQUAD m_color;					/*< Light color, defaults to white. */
	Vector3 m_intensity;				/*< Light color in Vector3 format. */
	LightSourceType m_type;				/*< Light Source type */

	/**
	 * \fn      LightSource
	 * \brief   Default constructor.
	 */
	LightSource();

public:

	/**
	 * \fn      LightSource
	 * \brief   Copy constructor.
	 */
	LightSource(const LightSource& pCopy);

	/**
	 * \fn      LightSource
	 * \brief   Recommended Constructor.
	 *
	 * \param[in]   pColor	Light color.
	 * \param[in]   pType	LightSource type.
	 */
	LightSource(LightSourceType pType, RGBQUAD pColor = { 255, 255, 255, 255 });

	inline const int& id() const { return m_lightID; }
	inline const LightSourceType& type() const { return m_type; }
	inline const Vector3& intensity() const { return m_intensity; }
	inline Vector3& intensity() { return m_intensity; }

	/*inline const RGBQUAD& color() const { return m_color; }
	inline RGBQUAD& color() { return m_color; }*/
};