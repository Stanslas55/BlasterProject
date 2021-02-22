#pragma once

#include "FreeImage.h"
#include "../Vector3/Vector3.hpp"
#include "../PrimitiveObjects/Plane.h"
#include "../PrimitiveObjects/Quadri.h"

class Camera {

private:

	static const int defaultWidth;
	static const int defaultHeight;
	static const RGBQUAD defaultBackgroundColor;

	Vector3 m_position;			/*< Position in the world reference */
	Vector3 m_rotation;			/*< Rotation of the camera in euler angles */

	Plane m_focalPlane;			/*< Focal plane at 1.0f units of the camera */
	Plane m_nearPlane;			/*< Near plane at 0.1f units of the camera */
	Plane m_farPlane;			/*< Far plane  at 100.0f units of the camera */

	RGBQUAD m_backgroundColor;	/*< Background color. Returned when no intersection point has been found for a pixel. */

	Vector3 m_corners[4];		/*< Corners of the image projected on the focal plane */
	double m_offset;

	int m_width;				/*< Width of the image taken by the camera */
	int m_height;				/*< Height of the image taken by the camera */

	//Vector3 getPixelPosition(int pX, int pY);

public:

	friend class Scene;

	/**
	 * \fn		Camera
	 * \brief	Default constructor.
	 *
	 */
	Camera();

	/**
	 * \fn		Camera
	 * \brief   Recommanded constructor.
	 *
	 * \param   pWidth		Image width
	 * \param   pHeight		Image height
	 */
	Camera(const int pWidth, const int pHeight, RGBQUAD pBackgroundColor = defaultBackgroundColor);
	
	/**
	 * \fn		Camera
	 * \brief   Copy constructor.
	 * 
	 * \param   pCopy
	 */
	Camera(const Camera& pCopy);

	/**
	 * \fn      ratio
	 * \brief   Compute ratio of the image.
	 * 
	 * \return  const double	width/height
	 */
	inline const double ratio() const { return m_width / m_height; }

	/**
	 * \fn      operator=
	 * \brief	Assignment operator. Creates a copy of this camera
	 * 
	 * \param   pOther		Copied camera
	 * \return  Camera& 
	 */
	Camera& operator=(const Camera& pOther);
};