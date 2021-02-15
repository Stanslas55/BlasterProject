#include "Tri.h"

Tri::Tri() : Polygon(3, Vector3(0, 0, 0), Vector3(0, 0, 0)) {
	m_corners[0] = Vector3(0, 0, 0);
	m_corners[1] = Vector3(0, 0, 0);
	m_corners[2] = Vector3(0, 0, 0);
}

Tri::Tri(const Tri & pCopy) : Polygon(3, pCopy.m_center, pCopy.m_normal) {
	m_corners[0] = pCopy.A();
	m_corners[1] = pCopy.B();
	m_corners[2] = pCopy.C();
}

Tri::Tri(Vector3 pCorners[3], const Vector3& pCenter, const Vector3& pNormal): Polygon(3, pCenter, pNormal) {
	m_corners[0] = pCorners[0];
	m_corners[1] = pCorners[1];
	m_corners[2] = pCorners[2];
}

Tri::~Tri() {}

std::vector<Vector3> Tri::intersect(const Ray& pRay) const {
	return Polygon::intersect(pRay);
}

Tri Tri::fromPoints(Vector3 pCorners[3]) {
	Vector3 corners[3], center, normal;

	corners[0] = pCorners[0];
	corners[1] = pCorners[1];
	corners[2] = pCorners[2];	

	double moyenneX = (corners[0].x() + corners[1].x() + corners[2].x()) / 3;
	double moyenneY = (corners[0].y() + corners[1].y() + corners[2].y()) / 3;
	double moyenneZ = (corners[0].z() + corners[1].z() + corners[2].z()) / 3;

	center = Vector3(moyenneX, moyenneY, moyenneZ);

	normal = Vector3::normalize(Vector3::cross(corners[0] - corners[1], corners[2] - corners[1]));

	return Tri(corners, center, normal);
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