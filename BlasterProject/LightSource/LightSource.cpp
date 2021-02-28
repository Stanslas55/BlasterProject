#include "LightSource.hpp"

int LightSource::currentId = 0;

LightSource::LightSource() {
	m_intensity = Vector3(255, 255, 255);
	m_lightID = currentId++;
	m_type = LightSourceType::NONE;
	m_fAtt = AttenuationFunction();
}

LightSource::LightSource(const LightSource& pCopy) {
	m_intensity = pCopy.m_intensity;
	m_lightID = pCopy.m_lightID;
	m_type = pCopy.m_type;
	m_fAtt = pCopy.m_fAtt;
}

LightSource::LightSource(LightSourceType pType, RGBQUAD pColor, const AttenuationFunction& pFatt) {
	m_intensity = Vector3(pColor.rgbRed, pColor.rgbGreen, pColor.rgbBlue);
	m_lightID = currentId++;
	m_type = pType;
	m_fAtt = pFatt;
}