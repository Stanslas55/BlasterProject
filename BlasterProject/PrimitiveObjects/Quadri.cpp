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

Quadri::~Quadri() {}

std::vector<Vector3> Quadri::intersect(const Ray& pRay) const {
	
	return Polygon::intersect(pRay);
}

Quadri Quadri::fromPoints(Vector3 pCorners[4]) {
	
	Vector3 corners[4], center, normal;

	corners[0] = pCorners[0];
	corners[1] = pCorners[1];
	corners[2] = pCorners[2];
	corners[3] = pCorners[3];

	double moyenneX = (corners[0].x() + corners[1].x() + corners[2].x() + corners[3].x()) / 4;
	double moyenneY = (corners[0].y() + corners[1].y() + corners[2].y() + corners[3].y()) / 4;
	double moyenneZ = (corners[0].z() + corners[1].z() + corners[2].z() + corners[3].z()) / 4;

	center = Vector3(moyenneX, moyenneY, moyenneZ);
	
	normal = Vector3::normalize(Vector3::cross(corners[0] - corners[1], corners[2] - corners[1]));

	return Quadri(corners, center, normal);
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