#include "Vector3.hpp"

const Vector3 Vector3::zero = Vector3(0.0, 0.0, 0.0);

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
	if (*this == Vector3::zero)
		return; // A vérifier.
	
	this->division(sqrt(x() * x() + y() * y() + z() * z()));
}

Vector3 Vector3::normalize(const Vector3& pV) {
	
	if (pV == Vector3::zero)
		return Vector3::zero; // A vérifier.

	return pV / sqrt(pV.m_data[0] * pV.m_data[0] + pV.m_data[1] * pV.m_data[1] + pV.m_data[2] * pV.m_data[2]);
}

const double Vector3::magnitude() const {
	return sqrt(pow(m_data[0], 2) + pow(m_data[1], 2) + pow(m_data[2], 2));
}

const double Vector3::distance(const Vector3& pA, const Vector3& pB) {
	return sqrt(pow(pA.m_data[0] - pB.m_data[0], 2) + pow(pA.m_data[1] - pB.m_data[1], 2) + pow(pA.m_data[2] - pB.m_data[2], 2));
}

const double Vector3::sqDdistance(const Vector3& pA, const Vector3& pB) {
	return pow(pA.m_data[0] - pB.m_data[0], 2) + pow(pA.m_data[1] - pB.m_data[1], 2) + pow(pA.m_data[2] - pB.m_data[2], 2);
}

const Vector3 Vector3::toPolar(const Vector3& pV) {
	return Vector3(
		pV.magnitude(),
		atan2(sqrt(pow(pV.x(), 2) + pow(pV.y(), 2)), pV.z()),
		atan2(pV.y(), pV.x())
	);
}

const Vector3 Vector3::toCarthesian(const Vector3& pV) {
	return Vector3(
		pV.x() * sin(pV.y()) * cos(pV.z()),
		pV.x() * sin(pV.y()) * sin(pV.z()),
		pV.x() * cos(pV.y())
	);
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

Vector3& Vector3::operator+=(const Vector3& pV) {
	m_data[0] += pV.m_data[0];
	m_data[1] += pV.m_data[1];
	m_data[2] += pV.m_data[2];
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& pV) {
	m_data[0] -= pV.m_data[0];
	m_data[1] -= pV.m_data[1];
	m_data[2] -= pV.m_data[2];
	return *this;
}

Vector3& Vector3::operator*=(const double& pScalar) {
	m_data[0] *= pScalar;
	m_data[1] *= pScalar;
	m_data[2] *= pScalar;
	return *this;
}

Vector3& Vector3::operator/=(const double& pScalar) {
	m_data[0] /= pScalar;
	m_data[1] /= pScalar;
	m_data[2] /= pScalar;
	return *this;
}

const Vector3 Vector3::operator-() const {
	return Vector3(
		-m_data[0],
		-m_data[1],
		-m_data[2]
	);
}

const bool operator==(const Vector3& pA, const Vector3& pB) {

	if (pA.x() == pB.x() && pA.y() == pB.y() && pA.z() == pB.z()) return true;
	return false;	 
}

const bool operator!=(const Vector3& pA, const Vector3& pB) {

	if (pA.x() == pB.x() && pA.y() == pB.y() && pA.z() == pB.z()) return false;
	return true;
}

std::ostream& operator<<(std::ostream& pFlux, const Vector3& pV) {
	pV.print(pFlux);
	return pFlux;
}

Vector3 operator+(const Vector3& pA, const Vector3& pB) {
	Vector3 result(pA);
	result.addition(pB);
	return result;
}

Vector3 operator-(const Vector3& pA, const Vector3& pB) {
	Vector3 result(pA);
	result.substraction(pB);
	return result;
}

Vector3 operator*(const Vector3& pA, double pScalar) {
	Vector3 result(pA);
	result.multiplication(pScalar);
	return result;
}

Vector3 operator/(const Vector3& pA, double pScalar) {
	Vector3 result(pA);
	result.division(pScalar);
	return result;
}

double operator*(const Vector3& pA, const Vector3& pB){
	return pA.dot(pB);
}