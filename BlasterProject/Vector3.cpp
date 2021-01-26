#include "Vector3.hpp"

Vector3::Vector3() {
	data = new float[3];
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
}

Vector3::Vector3(const Vector3& pV) {
	data = new float[3];
	data[0] = pV.data[0];
	data[1] = pV.data[1];
	data[2] = pV.data[2];	
}

Vector3::Vector3(float pX, float pY, float pZ) {
	data = new float[3];
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

Vector3 Vector3::substraction(Vector3& pV) {
	return Vector3(data[0] - pV.data[0], data[1] - pV.data[1], data[2] - pV.data[2]);
}

float Vector3::dot(Vector3& pV) {
	return pV.data[0] * data[0] + pV.data[1] * data[1] + pV.data[2] * data[2];
}

Vector3 Vector3::multiplication(float pScalar) {
	return Vector3(data[0] * pScalar, data[1] * pScalar, data[2] * pScalar);
}

Vector3 Vector3::division(float pScalar) {
	if (pScalar == 0)
	{
		std::cout << "Division par 0 !" << std::endl;
		exit(-1);
	}
	return Vector3(data[0] / pScalar, data[1] / pScalar, data[2] / pScalar);
}

void Vector3::print(std::ostream& pFlux) {
	pFlux << "(" << this->x() << ", " << this->y() << ", " << this->z() << ")";
}

Vector3& Vector3::operator=(const Vector3& pOther) {
	if (this == &pOther) {
		return *this;
	}

	if (data == nullptr) {
		data = new float[3];
	}

	data[0] = pOther.data[0];
	data[1] = pOther.data[1];
	data[2] = pOther.data[2];

	return *this;
}

// TODO: Écrire la fonction.
Vector3 normalize(const Vector3& pOther) {
	return Vector3();
}
// TODO: Écrire la fonction.
Vector3 normalize() {
	return Vector3();
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

Vector3 operator*(Vector3 pA, float pScalar) {
	return pA.multiplication(pScalar);
}

Vector3 operator/(Vector3 pA, float pScalar) {
	return pA.division(pScalar);	
}

float operator*(Vector3 pA, Vector3 pB){
	return pA.dot(pB);
}