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

Material::Material(const std::shared_ptr<RGBQUAD[]>& pTexture, const int pWidth, const int pHeight, const Vector3 pPoints[3], const Vector3 pVertex[3], double pKa, double pKd, double pKs, double pKe) {

	m_width = pWidth;
	m_height = pHeight;

	m_texture = pTexture;

	m_ka = pKa;
	m_kd = pKd;
	m_ks = pKs;
	m_ke = pKe;

	m_points[0] = pPoints[0];
	m_points[1] = pPoints[1];
	m_points[2] = pPoints[2];

	m_AB = Vector3::distance(m_points[0], m_points[1]);
}

/*Material::Material(const std::string pPathTexture, double pKa, double pKd, double pKs, double pKe) {
	m_ka = pKa;
	m_kd = pKd;
	m_ks = pKs;
	m_ke = pKe;	

	FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(pPathTexture.c_str());
	FIBITMAP* bmp = FreeImage_Load(fif, pPathTexture.c_str());

	unsigned w = FreeImage_GetWidth(bmp);
	unsigned h = FreeImage_GetHeight(bmp);
	m_width = w;
	m_height = h;
	int i, wh = w * h;
	
	m_texture = std::shared_ptr<RGBQUAD[]>(new RGBQUAD[wh]);
	// Parcourir l'image de taille width*height
#pragma omp parallel for
	for (i = 0; i < wh; i++) {

		const int x = i % w;
		const int y = h - i / w;
		RGBQUAD color = { 0, 0, 0, 255 };
		FreeImage_GetPixelColor(bmp, x, y, &color);
		//std::cout << color.rgbRed << " " << color.rgbGreen << " " << color.rgbBlue << std::endl;
		m_texture[i] = color;
	}
	std::cout << "Texture file loaded" << std::endl;
}*/

RGBQUAD Material::getColor(const Vector3& pA, const Vector3& pB, const Vector3& pP) const
{
	if (!m_texture)
		return m_Ia;

	const double angle = Vector3::angle(pA, pB, pP);
	double ratioAPAB = Vector3::sqDdistance(pA, pP) / Vector3::sqDdistance(pA, pB);

	const double dist = m_AB * ratioAPAB;
	const int x = dist * cos(angle) * double(m_width);
	const int y = dist * sin(angle) * double(m_height);
	return m_texture.get()[x + y * m_width];
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