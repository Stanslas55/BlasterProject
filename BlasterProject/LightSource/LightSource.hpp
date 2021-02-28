#pragma once

#include "FreeImage.h"
#include "Vector3/Vector3.hpp"

enum class LightSourceType {
	POINT,
	DIRECTIONAL,

	NONE
};

class AttenuationFunction {

protected:
	double m_coef = 1.0;

public:
	friend class LightSource;

	virtual void precomputeCoeff(const double pDist = 0.0) {}

	const Vector3 fAtt(const Vector3& pV) {
		return pV * m_coef;
	}
};

class ConstantAttenuation : public AttenuationFunction {

private:

public:
	ConstantAttenuation(const double pCoef = 1.0) {
		m_coef = pCoef;
	}

	void precomputeCoeff(const double pDist) {}
};

class RealisticAttenuation : public AttenuationFunction {

private:

public:
	RealisticAttenuation() {}

	void precomputeCoeff(const double pDist = 0.0) {
		m_coef = pDist == 0.0 ? 1.0 : 1.0 / pDist;
	}
};

class LinearAttenuation : public AttenuationFunction {

private:
	const double m_kc;
	const double m_kl;

public:
	LinearAttenuation(const double pKc = 1.0, const double pKl = 0.1) : m_kc(pKc == 0 ? 1.0 : pKc), m_kl(pKl) {}

	void precomputeCoeff(const double pDist = 0.0) {
		m_coef = 1.0 / (m_kc + pDist * m_kl);
	}
};

class QuadraticAttenuation : public AttenuationFunction {

private:
	const double m_kc;
	const double m_kl;
	const double m_kq;

public:
	QuadraticAttenuation(const double pKc = 1.0, const double pKl = 0.1, const double pKq = 1.0) : m_kc(pKc == 0 ? 1.0 : pKc), m_kl(pKl), m_kq(pKq) {}

	void precomputeCoeff(const double pDist = 0.0) {
		if (m_kc == 0.0 && pDist == 0.0)
			m_coef = 1.0;
		else
			m_coef = 1.0 / (m_kc + pDist * m_kl + m_kq * pDist * pDist);
	}
};

/**
 * \class	LightSource
 * \brief	Base light source class
 */
class LightSource {

protected:

	static int currentId;				/*< Counter of current light ID. Each LightSource has a unique ID. */

	int m_lightID;						/*< This light's Identifier. */
	Vector3 m_intensity;				/*< Light color in Vector3 format. */
	LightSourceType m_type;				/*< Light Source type */

	AttenuationFunction m_fAtt;

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
	LightSource(LightSourceType pType, RGBQUAD pColor = { 255, 255, 255, 255 }, const AttenuationFunction& pFatt = AttenuationFunction());

	inline AttenuationFunction& fAtt() { return m_fAtt; }

	inline const int& id() const { return m_lightID; }
	inline const LightSourceType& type() const { return m_type; }
	inline const Vector3& intensity() const { return m_intensity; }
	inline Vector3& intensity() { return m_intensity; }

	/*inline const RGBQUAD& color() const { return m_color; }
	inline RGBQUAD& color() { return m_color; }*/
};