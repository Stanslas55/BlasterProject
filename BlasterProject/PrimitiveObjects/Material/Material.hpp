#pragma once
#include <iostream>
#include "Vector3/Vector3.hpp"
#include "Matrix4/Matrix4.hpp"
#include "FreeImage.h"

/**
 * \class	Material
 * \brief	Base class for material
 */
class Material {

protected:

	RGBQUAD m_Ia;				/*< Color of the material */

	double m_ka;				/*< Ambiant reflection coefficient */
	double m_kd;				/*< Diffuse reflection coefficient */
	double m_ks;				/*< Specular reflection coefficient */
	double m_ke;				/*< Specular Exponent (shiness). Ranges from 0.0 to 100.0. */

public:

	static Material defaultMaterial;

	/**
	 * \fn      Material
	 * \brief   Default constructor.
	 */
	Material();

	/**
	 * \fn      Material
	 * \brief   Recommended constructor.
	 *
	 * \param[in]   pColor
	 * \param[in]   pKa		Ambiant reflection coefficient. Defaults to 1.0.
	 * \param[in]   pKd		Diffuse reflection coefficient. Defaults to 1.0.
	 * \param[in]   pKs		Specular reflection coefficient. Defaults to 1.0.
	 * \param[in]   pKe		Specular Exponent (shiness). Ranges from 0.0 to 100.0. Defaults to 0.0.
	 */
	Material(RGBQUAD pColor, double pKa = 1.0, double pKd = 1.0, double pKs = 1.0, double pKe = 0.0);

	/**
	 * \fn      operator=
	 * \brief   Assignation operator.
	 *
	 * \param[in]   pOther
	 * \return      Material&	Reference to this after being assigned pOther
	 */
	Material& operator=(const Material& pOther);

	inline const RGBQUAD& color() const { return m_Ia; }
	inline RGBQUAD& color() { return m_Ia; }

	inline const double& ka() const { return m_ka; }
	inline double& ka() { return m_ka; }

	inline const double& kd() const { return m_kd; }
	inline double& kd() { return m_kd; }

	inline const double& ks() const { return m_ks; }
	inline double& ks() { return m_ks; }

	inline const double& ke() const { return m_ke; }
	inline double& ke() { return m_ke; }

	/**
	 * \fn      randomMaterial
	 * \brief   Generates a random Material. Beware, it WILL be hideous.
	 *
	 * \return	const Material
	 */
	static const Material randomMaterial();
};

/**
 * \fn      operator<<
 * \brief   Write a material to a output stream.
 *
 * \param[in]   pFlux
 * \param[in]   pM
 * \return      std::ostream&
 */
std::ostream& operator<<(std::ostream& pFlux, const Material& pM);
