#include "Vector3.hpp"

Vector3::Vector3() {
	m_data[0] = 0.0;
	m_data[1] = 0.0;
	m_data[2] = 0.0;
}

Vector3::Vector3(const Vector3& pV) {
	m_data[0] = pV.m_data[0];
	m_data[1] = pV.m_data[1];
	m_data[2] = pV.m_data[2];	
}

Vector3::Vector3(double pX, double pY, double pZ) {
	m_data[0] = pX;
	m_data[1] = pY;
	m_data[2] = pZ;
}

Vector3::~Vector3() {}

void Vector3::addition(const Vector3& pV) {	
	m_data[0] += pV.m_data[0];
	m_data[1] += pV.m_data[1];
	m_data[2] += pV.m_data[2];
}

void Vector3::substraction(const Vector3& pV) {
	m_data[0] -= pV.m_data[0];
	m_data[1] -= pV.m_data[1];
	m_data[2] -= pV.m_data[2];
}

double Vector3::dot(const Vector3& pV) const{
	return pV.m_data[0] * m_data[0] + pV.m_data[1] * m_data[1] + pV.m_data[2] * m_data[2];
}

void Vector3::multiplication(double pScalar) {

	m_data[0] *= pScalar;
	m_data[1] *= pScalar;
	m_data[2] *= pScalar;
}

void Vector3::division(double pScalar) {
	if (pScalar == 0)
	{
		std::cout << "Division par 0 !" << std::endl;
		exit(-1);
	}
	m_data[0] /= pScalar;
	m_data[1] /= pScalar;
	m_data[2] /= pScalar;
}

void Vector3::cross(const Vector3& pV) {		

	double x, y, z;
	x = m_data[1] * pV.m_data[2] - m_data[2] * pV.m_data[1];
	y = m_data[2] * pV.m_data[0] - m_data[0] * pV.m_data[2];
	z = m_data[0] * pV.m_data[1] - m_data[1] * pV.m_data[0];	

	m_data[0] = x;
	m_data[1] = y;
	m_data[2] = z;
}

Vector3 Vector3::cross(const Vector3& pA, const Vector3& pB) {
	Vector3 result(pA);	
	result.cross(pB);
	return result;
}

void Vector3::normalize() {
	double norme;
	Vector3 pTest(m_data[0], m_data[1], m_data[2]);
	if (pTest  == Vector3(0, 0, 0)) return; // A vérifier.
	norme = sqrt(x() * x() + y() * y() + z() * z());
	
	this->division(norme);
}

Vector3 Vector3::normalize(const Vector3& pV) {
	
	Vector3 result(pV);
	
	Vector3 pTest(pV.x(), pV.y(), pV.z());
	if (pTest == Vector3(0, 0, 0)) return pV; // A vérifier.
	result.division(sqrt(pV.m_data[0] * pV.m_data[0] + pV.m_data[1] * pV.m_data[1] + pV.m_data[2] * pV.m_data[2]));
	return result;
}

void Vector3::print(std::ostream& pFlux) const {
	pFlux << "(" << x() << ", " << y() << ", " << z() << ")";
}

Vector3& Vector3::operator=(const Vector3& pOther) {
	if (this == &pOther) {
		return *this;
	}

	m_data[0] = pOther.m_data[0];
	m_data[1] = pOther.m_data[1];
	m_data[2] = pOther.m_data[2];

	return *this;
}

const bool operator==(const Vector3& pA, const Vector3& pB) {

	if (pA.x() == pB.x() && pA.y() == pB.y() && pA.z() == pB.z()) return true;
	return false;	 
}

std::ostream& operator<<(std::ostream& pFlux, Vector3 pV) {
	pV.print(pFlux);
	return pFlux;
}

Vector3 operator+(Vector3 pA, Vector3 pB) {
	Vector3 result(pA);
	result.addition(pB);
	return result;
}

Vector3 operator-(Vector3 pA, Vector3 pB) {	
	Vector3 result(pA);
	result.substraction(pB);
	return result;
}

Vector3 operator*(Vector3 pA, double pScalar) {
	Vector3 result(pA);
	result.multiplication(pScalar);
	return result;
}

Vector3 operator/(Vector3 pA, double pScalar) {
	Vector3 result(pA);
	result.division(pScalar);
	return result;
}

double operator*(Vector3 pA, Vector3 pB){
	return pA.dot(pB);
}