#pragma once
#include <iostream>

class Vector3{
	private:		
		float* data = nullptr;	

	public:	
		inline float& x() { return data[0]; }
		inline float& y() { return data[1]; }
		inline float& z() { return data[2]; }

		Vector3();
		Vector3(const Vector3& pV);
		Vector3(float pX, float pY, float pZ);
		~Vector3();

		Vector3 addition(const Vector3& pV);
		Vector3 substraction(Vector3& pV);
		float dot(Vector3& pV);
		Vector3 multiplication(float pScalar);
		Vector3 division(float pScalar);
		// Normalize this vector.		
		void normalize(); 
		// Return a new vector which is the normalized pV.
		static Vector3 normalize(const Vector3& pV); 

		void print(std::ostream& flux);
		Vector3& operator=(const Vector3& pOther);		
};

std::ostream& operator<<(std::ostream& pFlux, Vector3 pV);
Vector3 operator+(Vector3 pA, Vector3 pB);
Vector3 operator-(Vector3 pA, Vector3 pB);

Vector3 operator*(Vector3 pA, float pScalar);
Vector3 operator/(Vector3 pA, float pScalar);
float operator*(Vector3 pA, Vector3 pB);