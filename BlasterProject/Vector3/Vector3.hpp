#pragma once
#include <iostream>
#include <math.h>

class Vector3{
	private:		
		double* data = nullptr;	

	public:	
		inline double& x() { return data[0]; }
		inline double& y() { return data[1]; }
		inline double& z() { return data[2]; }

		Vector3();
		Vector3(const Vector3& pV);
		Vector3(double pX, double pY, double pZ);
		~Vector3();

		Vector3 addition(const Vector3& pV);
		Vector3 substraction(Vector3& pV);
		double dot(Vector3& pV);
		Vector3 multiplication(double pScalar);
		Vector3 division(double pScalar);
		Vector3 cross(Vector3& pV);
		// Normalize this vector.		
		void normalize(); 
		// Return a new vector which is the normalized pV.
		static Vector3 normalize(Vector3& pV); 

		void print(std::ostream& flux);
		Vector3& operator=(const Vector3& pOther);		
};

std::ostream& operator<<(std::ostream& pFlux, Vector3 pV);
Vector3 operator+(Vector3 pA, Vector3 pB);
Vector3 operator-(Vector3 pA, Vector3 pB);

Vector3 operator*(Vector3 pA, double pScalar);
Vector3 operator/(Vector3 pA, double pScalar);
double operator*(Vector3 pA, Vector3 pB);