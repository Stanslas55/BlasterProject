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
		/**
		 *  \fn     addition
		 *  \brief  Add a Vector3 to another Vector3.
		 *
		 *  \param[in]      pV              The Vector3 to add to the Vector3.		
		 *  \return         Vector3			The resulting added Vector3.
		 */
		Vector3 addition(const Vector3& pV);
		/**
		 *  \fn     substraction
		 *  \brief  Substracts a Vector3 to another one.
		 *
		 *  \param[in]      pV              The Vector3 to substract to the Vector3.		
		 *  \return         Vector3         The resulting substracted Vector3.
		 */
		Vector3 substraction(const Vector3& pV);
		/**
		 *  \fn     dot
		 *  \brief  Performs the dot product between 2 Vector3.
		 *
		 *  \param[in]      pV              The Vector3 which will be used to perform the dot product. this * pV.		
		 *  \return         double			The resulting dot product.
		 */
		double dot(const Vector3& pV);
		/**
		 *  \fn     multiplication
		 *  \brief  Multiplies a Vector3 with a double.
		 *
		 *  \param[in]      pScalar         The double which will multiply the Vector3.		
		 *  \return         Vector3			The resulting multiplied Vector3.
		 */
		Vector3 multiplication(double pScalar);
		/**
		 *  \fn     division
		 *  \brief  Divides a VEctor3 by a double.
		 *
		 *  \param[in]      pScalar         The double which will divide the Vector3.		
		 *  \return         Vector3		    The resulting divided Vector3.
		 */
		Vector3 division(double pScalar);
		/**
		 *  \fn     cross
		 *  \brief  Performs the cross product between 2 Vector3.
		 *
		 *  \param[in]      pV              The Vector3 which will be used to perform the cross product. this ^ pV.		
		 *  \return         Vector3			The resulting cross product.
		 */
		Vector3 cross(Vector3& pV);		
		/**
		 *  \fn     normalize
		 *  \brief  Normalizes the vector. The object is modified.
		 *		
		 */
		void normalize(); 	
		/**
		 *  \fn     normalize
		 *  \brief  Normalizes a copy of pV. Usage: Vector3().normalize(pV);
		 *
		 *  \param[in]      pV              The Vector3 to be normalized.		
		 *  \return         Vector3			The resulting normalized Vector3.
		 */
		static Vector3 normalize(Vector3& pV); 
		/**
		 *  \fn     print
		 *  \brief  Print a Vector3.
		 *
		 *  \param[in]      pFlux           The flux where the Vector3 has to be printed.		
		 *  \return         void			This function returns nothing.
		 */
		void print(std::ostream& pFlux);
		Vector3& operator=(const Vector3& pOther);		
};

std::ostream& operator<<(std::ostream& pFlux, Vector3 pV);
Vector3 operator+(Vector3 pA, Vector3 pB);
Vector3 operator-(Vector3 pA, Vector3 pB);

Vector3 operator*(Vector3 pA, double pScalar);
Vector3 operator/(Vector3 pA, double pScalar);
double operator*(Vector3 pA, Vector3 pB);