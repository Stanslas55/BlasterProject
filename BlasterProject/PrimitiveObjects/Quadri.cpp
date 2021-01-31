#include "Quadri.h"

Quadri::Quadri(): Polygon(4, Vector3(0,0,0), Vector3(0,0,0)) {	
	m_corners[0] = Vector3(0, 0, 0);
	m_corners[1] = Vector3(0, 0, 0);
	m_corners[2] = Vector3(0, 0, 0);
	m_corners[3] = Vector3(0, 0, 0);
	
}

Quadri::Quadri(const Quadri& pCopy): Polygon(4, pCopy.m_center, pCopy.m_normal) {
	m_corners[0] = pCopy.A();
	m_corners[1] = pCopy.B();
	m_corners[2] = pCopy.C();
	m_corners[3] = pCopy.D();
}

Quadri::Quadri(Vector3 pCorners[4], const Vector3& pCenter, const Vector3& pNormal): Polygon(4, pCenter, pNormal) {

	m_corners[0] = pCorners[0];
	m_corners[1] = pCorners[1];
	m_corners[2] = pCorners[2];
	m_corners[3] = pCorners[3];
}

Quadri::~Quadri()
{	
}

std::vector<Vector3> Quadri::intersect(const Ray& pRay) const {
	
	std::vector<Vector3> point = Polygon::intersect(pRay);	

	if (point.size() != 0) {
		std::cout << "Chercher si le point est dans le Quadri." << std::endl;
		// Rechercher si point[0] appartient au Quadrilatère.

		return std::vector<Vector3>(); // A changer.
	}
	std::cout << "No intersection between the quadri and the ray." << std::endl;
	return std::vector<Vector3>();
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
	corners(0) = pOther.A();
	corners(1) = pOther.B();
	corners(2) = pOther.C();
	corners(3) = pOther.D();
	return *this;
}

std::ostream& operator<<(std::ostream& pFlux, const Quadri& pQuadri) {
	pQuadri.print(pFlux);
	return pFlux;
}