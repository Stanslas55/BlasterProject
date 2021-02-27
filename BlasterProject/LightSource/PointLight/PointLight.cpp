#include "PointLight.hpp"

PointLight::PointLight() : LightSource(LightSourceType::POINT, { 255, 255, 255, 255 }) {
	m_position = Vector3::zero;
}

PointLight::PointLight(Vector3 pPosition, RGBQUAD pColor, const AttenuationFunction& pFatt) : LightSource(LightSourceType::POINT, pColor, pFatt) {
	m_position = pPosition;
}