#include "Vector3.hpp"

Vector3::Vector3() {
	data = new double[3];
	data[0] = -10;
	data[1] = -10;
	data[2] = -10;
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
	delete[] data;
	data = nullptr;
}

Vector3 Vector3::addition(const Vector3& pV) {	
	return Vector3(data[0] + pV.data[0], data[1] + pV.data[1], data[2] + pV.data[2]);
}

Vector3 Vector3::substraction(const Vector3& pV) {
	return Vector3(data[0] - pV.data[0], data[1] - pV.data[1], data[2] - pV.data[2]);
}

double Vector3::dot(const Vector3& pV) {
	return pV.data[0] * data[0] + pV.data[1] * data[1] + pV.data[2] * data[2];
}

Vector3 Vector3::multiplication(double pScalar) {
	return Vector3(data[0] * pScalar, data[1] * pScalar, data[2] * pScalar);
}

Vector3 Vector3::division(double pScalar) {
	if (pScalar == 0)
	{
		std::cout << "Division par 0 !" << std::endl;
		exit(-1);
	}
	return Vector3(data[0] / pScalar, data[1] / pScalar, data[2] / pScalar);
}

Vector3 Vector3::cross(const Vector3& pV) const
{	
	return Vector3(data[1] * pV.data[2] - data[2] * pV.data[1], data[2] * pV.data[0] - data[0] * pV.data[2], data[0] * pV.data[1] - data[1] * pV.data[0]);
}

void Vector3::normalize()
{
	double norme;
	norme = sqrt(x() * x() + y() * y() + z() * z());
	
	*this = this->division(norme);
}

Vector3 Vector3::normalize(const Vector3& pV)
{
	double norme;
	Vector3 result = pV;

	norme = sqrt(pV.data[0] * pV.data[0] + pV.data[1] * pV.data[1] + pV.data[2] * pV.data[2]);
	result = result.division(norme);

	return result;
}

void Vector3::print(std::ostream& pFlux) {
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

std::ostream& operator<<(std::ostream& pFlux, Vector3 pV) {
	pV.print(pFlux);
	return pFlux;
}

Vector3 operator+(Vector3 pA, Vector3 pB) {
	return pA.addition(pB);		
}

Vector3 operator-(Vector3 pA, Vector3 pB) {
	return pA.substraction(pB);	
}

Vector3 operator*(Vector3 pA, double pScalar) {
	return pA.multiplication(pScalar);
}

Vector3 operator/(Vector3 pA, double pScalar) {
	return pA.division(pScalar);	
}

double operator*(Vector3 pA, Vector3 pB){
	return pA.dot(pB);
}