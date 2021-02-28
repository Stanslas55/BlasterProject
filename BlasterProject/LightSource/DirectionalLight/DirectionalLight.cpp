#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight() : LightSource(LightSourceType::DIRECTIONAL) {
	m_direction = Vector3(0.0, 0.0, 0.0);
}

DirectionalLight::DirectionalLight(Vector3 pDirection, RGBQUAD pColor, const AttenuationFunction& pFatt) : LightSource(LightSourceType::DIRECTIONAL, pColor, pFatt) {
	m_direction = Vector3::normalize(pDirection);
}