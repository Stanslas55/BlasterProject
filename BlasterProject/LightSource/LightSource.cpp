#include "LightSource.hpp"

int LightSource::currentId = 0;

LightSource::LightSource() {
	m_color = { 255, 255, 255, 255 };
	m_intensity = Vector3(m_color.rgbRed, m_color.rgbGreen, m_color.rgbBlue);
	m_lightID = currentId++;
	m_type = LightSourceType::NONE;
}

LightSource::LightSource(const LightSource& pCopy) {
	m_color = pCopy.m_color;
	m_intensity = pCopy.m_intensity;
	m_lightID = pCopy.m_lightID;
	m_type = pCopy.m_type;
}

LightSource::LightSource(LightSourceType pType, RGBQUAD pColor) {
	m_color = pColor;
	m_intensity = Vector3(m_color.rgbRed, m_color.rgbGreen, m_color.rgbBlue);
	m_lightID = currentId++;
	m_type = pType;
}