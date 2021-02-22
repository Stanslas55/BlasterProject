#include "Tri.h"

Tri::Tri() : Polygon({ Vector3::zero, Vector3::zero, Vector3::zero }, Material::defaultMaterial) {}

Tri::Tri(const Tri & pCopy) : Polygon(pCopy) {}

Tri::Tri(const std::initializer_list<Vector3>& pCorners, const Material& pMaterial) : Polygon(pCorners, pMaterial) {}

Tri::Tri(const Vector3& pA, const Vector3& pB, const Vector3& pC, const Material& pMaterial) : Polygon({ pA, pB, pC }, pMaterial) {}

Tri::~Tri() {}

const Collision Tri::intersect(const Ray& pRay) const {
	return Polygon::intersect(pRay);
}

void Tri::print(std::ostream& pFlux) const {
	Polygon::print(std::cout);
	std::cout << "Tri: {" << A() << ", " << B() << ", " << C() << "}" << std::endl;
}

Tri& Tri::operator=(const Tri& pOther) {
	if (this == &pOther) {
		return *this;
	}
	m_center = pOther.m_center;
	m_normal = pOther.m_normal;
	m_corners[0] = pOther.A();
	m_corners[1] = pOther.B();
	m_corners[2] = pOther.C();

	return *this;
}

std::ostream& operator<<(std::ostream& pFlux, const Tri& pQuadri) {
	pQuadri.print(pFlux);
	return pFlux;
}