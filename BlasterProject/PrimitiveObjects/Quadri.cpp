#include "Quadri.h"

Quadri::Quadri() : Polygon({ Vector3::zero, Vector3::zero, Vector3::zero, Vector3::zero }, Material::defaultMaterial) {}

Quadri::Quadri(const Quadri& pCopy) : Polygon(pCopy) {}

Quadri::Quadri(const std::initializer_list<Vector3>& pCorners, const Material& pMaterial) : Polygon(pCorners, pMaterial) {}

Quadri::Quadri(const Vector3& pA, const Vector3& pB, const Vector3& pC, const Vector3& pD, const Material& pMaterial) : Polygon({ pA, pB, pC, pD }, pMaterial) {}

Quadri::~Quadri() {}

const Collision Quadri::intersect(const Ray& pRay) const {
	return Polygon::intersect(pRay);
}

void Quadri::print(std::ostream& pFlux) const {
	Polygon::print(std::cout);
	std::cout << "Quadri: {" << A() << ", " << B() << ", " << C() << ", " << D() << "}" << std::endl;
}

Quadri& Quadri::operator=(const Quadri& pOther) {
	if (this == &pOther) {
		return *this;
	}	
	m_center = pOther.m_center;
	m_normal = pOther.m_normal;
	m_corners[0] = pOther.A();
	m_corners[1] = pOther.B();
	m_corners[2] = pOther.C();
	m_corners[3] = pOther.D();
	
	return *this;
}

std::ostream& operator<<(std::ostream& pFlux, const Quadri& pQuadri) {
	pQuadri.print(pFlux);
	return pFlux;
}