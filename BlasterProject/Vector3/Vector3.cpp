#include "Vector3.hpp"

Vector3::Vector3() {
	data = new double[3];
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
}

Vector3::Vector3(const Vector3& pV) {
	data = new double[3];
	data[0] = pV.data[0];
	data[1] = pV.data[1];
	data[2] = pV.data[2];	
}

Vector3::Vector3(double pX, double pY, double pZ) {
	data = new double[3];
	data[0] = pX;
	data[1] = pY;
	data[2] = pZ;
}

Vector3::~Vector3() {
	if(data)	delete[] data;

	data = nullptr;
}

void Vector3::addition(const Vector3& pV) {	
	data[0] += pV.data[0];
	data[1] += pV.data[1];
	data[2] += pV.data[2];
}

void Vector3::substraction(const Vector3& pV) {
	data[0] -= pV.data[0];
	data[1] -= pV.data[1];
	data[2] -= pV.data[2];
}

double Vector3::dot(const Vector3& pV) const{
	return pV.data[0] * data[0] + pV.data[1] * data[1] + pV.data[2] * data[2];
}

void Vector3::multiplication(double pScalar) {

	data[0] *= pScalar;
	data[1] *= pScalar;
	data[2] *= pScalar;
}

void Vector3::division(double pScalar) {
	if (pScalar == 0)
	{
		std::cout << "Division par 0 !" << std::endl;
		exit(-1);
	}
	data[0] /= pScalar;
	data[1] /= pScalar;
	data[2] /= pScalar;
}

void Vector3::cross(const Vector3& pV) const {		

	double x, y, z;
	x = data[1] * pV.data[2] - data[2] * pV.data[1];
	y = data[2] * pV.data[0] - data[0] * pV.data[2];
	z = data[0] * pV.data[1] - data[1] * pV.data[0];	

	data[0] = x;
	data[1] = y;
	data[2] = z;
}

Vector3 Vector3::cross(const Vector3& pA, const Vector3& pB) {
	Vector3 result(pA);	
	result.cross(pB);
	return result;
}

void Vector3::normalize() {
	double norme;
	Vector3 pTest(data[0], data[1], data[2]);
	if (pTest  == Vector3(0, 0, 0)) return; // A vérifier.
	norme = sqrt(x() * x() + y() * y() + z() * z());
	
	this->division(norme);
}

Vector3 Vector3::normalize(const Vector3& pV) {
	
	Vector3 result(pV);
	
	Vector3 pTest(pV.x(), pV.y(), pV.z());
	if (pTest == Vector3(0, 0, 0)) return pV; // A vérifier.
	result.division(sqrt(pV.data[0] * pV.data[0] + pV.data[1] * pV.data[1] + pV.data[2] * pV.data[2]));
	return result;
}

void Vector3::print(std::ostream& pFlux) const {
	pFlux << "(" << x() << ", " << y() << ", " << z() << ")";
}

Vector3& Vector3::operator=(const Vector3& pOther) {
	if (this == &pOther) {
		return *this;
	}

	if (data == nullptr) {
		data = new double[3];
	}

	data[0] = pOther.data[0];
	data[1] = pOther.data[1];
	data[2] = pOther.data[2];

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