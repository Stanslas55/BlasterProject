#include "Material.hpp"

Material Material::defaultMaterial = Material();

Material::Material() {
	m_Ia = { 255, 255, 255, 255 };
	m_ka = 1.0;
	m_kd = 1.0;
	m_ks = 1.0;
	m_ke = 0.0;
}

Material::Material(RGBQUAD pColor, double pKa, double pKd, double pKs, double pKe) {
	m_Ia = pColor;
	m_ka = pKa;
	m_kd = pKd;
	m_ks = pKs;
	m_ke = pKe;
}

Material::Material(const std::shared_ptr<RGBQUAD[]>& pTexture, const int pWidth, const Vector3 pPoints[3], const Vector3 pVertex[3]) :m_width(pWidth)
{
	m_texture = pTexture;

	m_transform = Matrix4::changeBasis(pVertex, pPoints);
}

RGBQUAD Material::getColor(const Vector3& pV) const
{
	if (!m_texture)
		return m_Ia;

	const Vector3 v = m_transform * pV;
	return m_texture[v.x() + v.y()*m_width] ;
}

Material& Material::operator=(const Material& pOther) {

	if (this == &pOther) {
		return *this;
	}

	m_Ia = pOther.m_Ia;
	m_ka = pOther.m_ka;
	m_kd = pOther.m_kd;
	m_ks = pOther.m_ks;
	m_ke = pOther.m_ke;

	return *this;
}

std::ostream& operator<<(std::ostream& pFlux, const Material& pM) {
	pFlux << "Material : " << std::endl << "Color : " << pM.color() << std::endl << "kA : " << pM.ka() << std::endl << "kD : " << pM.kd() << std::endl << "kS : " << pM.ks() << std::endl << "kE : " << pM.ke() << std::endl;
	return pFlux;
}