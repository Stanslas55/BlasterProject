#include "Camera.hpp"

const int Camera::defaultWidth = 1280;
const int Camera::defaultHeight = 720;
const RGBQUAD Camera::defaultBackgroundColor = { 150, 150, 150 };

Camera::Camera() {
	m_position = Vector3(0.0, 0.0, 0.0);
	m_rotation = Vector3(0.0, 0.0, 0.0);

	Vector3 centerFocalPlane(0.0, 0.0, -1.0);

	m_focalPlane = Plane(centerFocalPlane, Vector3(0.0, 0.0, -1.0));
	m_nearPlane = Plane(Vector3(0.0, 0.0, -0.1), Vector3(0.0, 0.0, -1.0));
	m_farPlane = Plane(Vector3(0.0, 0.0, -100.0), Vector3(0.0, 0.0, -1.0));

	m_backgroundColor = defaultBackgroundColor;

	m_width = Camera::defaultWidth;
	m_height = Camera::defaultHeight;
	
	double distHeight = 1.0;
	double distWidth = distHeight * m_width / m_height;

	double distHeightd2 = distHeight / 2.0;
	double distWidthd2 = distWidth / 2.0;

	m_corners[0] = centerFocalPlane + Vector3(-distWidthd2, distHeightd2, 0.0);		// TopLeft
	m_corners[1] = centerFocalPlane + Vector3(distWidthd2, distHeightd2, 0.0);		// TopRight
	m_corners[2] = centerFocalPlane + Vector3(-distWidthd2, -distHeightd2, 0.0);	// BottomLeft
	m_corners[3] = centerFocalPlane + Vector3(distWidthd2, -distHeightd2, 0.0);		// BottomRight
	
	m_offset = distHeight / (m_height + 1);
}

Camera::Camera(const int pWidth, const int pHeight, RGBQUAD pBackgroundColor) {
	m_position = Vector3(0.0, 0.0, 0.0);
	m_rotation = Vector3(0.0, 0.0, 0.0);

	Vector3 centerFocalPlane(0.0, 0.0, -1.0);

	m_focalPlane = Plane(centerFocalPlane, Vector3(0.0, 0.0, -1.0));
	m_nearPlane = Plane(Vector3(0.0, 0.0, -0.1), Vector3(0.0, 0.0, -1.0));
	m_farPlane = Plane(Vector3(0.0, 0.0, -100.0), Vector3(0.0, 0.0, -1.0));

	m_backgroundColor = pBackgroundColor;
	
	m_width = pWidth;
	m_height = pHeight;

	double distHeight = 1.0;
	double distWidth = distHeight * m_width / m_height;

	double distHeightd2 = distHeight / 2.0;
	double distWidthd2 = distWidth / 2.0;

	m_corners[0] = centerFocalPlane + Vector3(-distWidthd2, distHeightd2, 0.0);		// TopLeft
	m_corners[1] = centerFocalPlane + Vector3(distWidthd2, distHeightd2, 0.0);		// TopRight
	m_corners[2] = centerFocalPlane + Vector3(-distWidthd2, -distHeightd2, 0.0);	// BottomLeft
	m_corners[3] = centerFocalPlane + Vector3(distWidthd2, -distHeightd2, 0.0);		// BottomRight

	m_offset = distHeight / (double(m_height) + 1.0);
}

Camera::Camera(const Camera& pCopy) {
	m_position = pCopy.m_position;
	m_rotation = pCopy.m_position;

	m_focalPlane = pCopy.m_focalPlane;
	m_nearPlane = pCopy.m_nearPlane;
	m_farPlane = pCopy.m_farPlane;

	m_backgroundColor = pCopy.m_backgroundColor;

	m_corners[0] = pCopy.m_corners[0];	// TopLeft
	m_corners[1] = pCopy.m_corners[1];	// TopRight
	m_corners[2] = pCopy.m_corners[2];	// BottomLeft
	m_corners[3] = pCopy.m_corners[3];	// BottomRight

	m_width = pCopy.m_width;
	m_height = pCopy.m_height;

	m_offset = pCopy.m_offset;
}

Camera& Camera::operator=(const Camera& pOther) {
	m_position = pOther.m_position;
	m_rotation = pOther.m_position;
	m_focalPlane = pOther.m_focalPlane;
	m_nearPlane = pOther.m_nearPlane;
	m_farPlane = pOther.m_farPlane;

	m_backgroundColor = pOther.m_backgroundColor;

	m_corners[0] = pOther.m_corners[0];	// TopLeft
	m_corners[1] = pOther.m_corners[1];	// TopRight
	m_corners[2] = pOther.m_corners[2];	// BottomLeft
	m_corners[3] = pOther.m_corners[3];	// BottomRight

	m_width = pOther.m_width;
	m_height = pOther.m_height;

	m_offset = pOther.m_offset;

	return *this;
}