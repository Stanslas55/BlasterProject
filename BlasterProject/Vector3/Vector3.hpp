#pragma once
#include <iostream>
#include <math.h>

class Vector3{
	private:			
		double m_data[3]{
			0.0, 0.0, 0.0
		};

	public:	
		
		static const Vector3 zero;

		inline double& x() { return m_data[0]; }
		inline double& y() { return m_data[1]; }
		inline double& z() { return m_data[2]; }

		inline const double& x() const { return m_data[0]; }
		inline const double& y() const { return m_data[1]; }
		inline const double& z() const { return m_data[2]; }

		Vector3();
		Vector3(const Vector3& pV);
		Vector3(double pX, double pY, double pZ);
		~Vector3();

		/**
		 *  \fn     addition
		 *  \brief  Add a Vector3 to this.
		 *
		 *  \param[in]      pV              The Vector3 to add to the Vector3.		
		 *  \return         void			
		 */
		void addition(const Vector3& pV);

		/**
		 *  \fn     substraction
		 *  \brief  Substracts a Vector3 to this.
		 *
		 *  \param[in]      pV              The Vector3 to substract to the Vector3.		
		 *  \return         void
		 */
		void substraction(const Vector3& pV);

		/**
		 *  \fn     dot
		 *  \brief  Performs the dot product between 2 Vector3.
		 *
		 *  \param[in]      pV              The Vector3 which will be used to perform the dot product. this * pV.		
		 *  \return         double			The resulting dot product.
		 */
		double dot(const Vector3& pV) const;

		/**
		 *  \fn     multiplication
		 *  \brief  Multiplies this by a double.
		 *
		 *  \param[in]      pScalar         The double which will multiply the Vector3.		
		 *  \return         void
		 */
		void multiplication(double pScalar);

		/**
		 *  \fn     division
		 *  \brief  Divides this by a double.
		 *
		 *  \param[in]      pScalar         The double which will divide the Vector3.		
		 *  \return         void
		 */
		void division(double pScalar);

		/**
		 *  \fn     cross
		 *  \brief  Performs the cross product between 2 Vector3.
		 *
		 *  \param[in]      pA              The Vector3 which will be used to perform the cross product. pA ^ pB.		
		 *  \param[in]      pB              The Vector3 which will be used to perform the cross product. 		
		 *  \return         Vector3			The resulting cross product.
		 */		
		static Vector3 cross(const Vector3& pA, const Vector3& pB); 

		/**
		 *  \fn     cross
		 *  \brief  Performs the cross product between this and a Vector3.
		 *
		 *  \param[in]      pV              The Vector3 which will be used to perform the cross product. this ^ pV.
		 *  \return         void			The resulting cross product.
		 */
		void cross(const Vector3& pV);

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
		static Vector3 normalize(const Vector3& pV); 

		/**
		 * \fn      distance
		 * \brief   Compute euclidian distance between two vectors.
		 * 
		 * \param[in]   pA
		 * \param[in]   pB
		 * \return      const double		Euclidian distance between pA and pB
		 */
		static const double distance(const Vector3& pA, const Vector3& pB);

		/**
		 * \fn      sqDistance
		 * \brief   Compute squared euclidian distance between two vectors.
		 *
		 * \param[in]   pA
		 * \param[in]   pB
		 * \return      const double		Sqared euclidian distance between pA and pB
		 */
		static const double sqDdistance(const Vector3& pA, const Vector3& pB);

		/**
		 *  \fn     print
		 *  \brief  Print a Vector3.
		 *
		 *  \param[in]      pFlux           The flux where the Vector3 has to be printed.		
		 *  \return         void			This function returns nothing.
		 */
		void print(std::ostream& pFlux) const;

		/**
		 * \fn      operator=
		 * \brief   Assignation operator.
		 * 
		 * \param[in]   pOther
		 * \return      Vector&		Reference to this after being assigned pOther
		 */
		Vector3& operator=(const Vector3& pOther);

		/**
		 * \fn      operator+=
		 * \brief   Add pV to this element-wise.
		 * 
		 * \param[in]   pV
		 * \return      Vector3&	this plus pV element-wise
		 */
		Vector3& operator+=(const Vector3& pV);

		/**
		 * \fn      operator-=
		 * \brief   Substract pV to this element-wise.
		 *
		 * \param[in]   pV
		 * \return      Vector3&	this minus pV element-wise
		 */
		Vector3& operator-=(const Vector3& pV);

		/**
		 * \fn      operator*=
		 * \brief   Multiply this by pScalar
		 *
		 * \param[in]   pScalar
		 * \return      Vector3&	this multiplied by pScalar
		 */
		Vector3& operator*=(const double& pScalar);

		/**
		 * \fn      operator/=
		 * \brief   Divide this by pScalar
		 *
		 * \param[in]   pScalar
		 * \return      Vector3&	this divided by pScalar
		 */
		Vector3& operator/=(const double& pScalar);

		/**
		 * \fn      operator-
		 * \brief   Unary minus operator.
		 *
		 * \return      const Vector3	-this
		 */
		const Vector3 operator-() const;
};

/**
 * \fn      operator<<
 * \brief   Write a vector to a output stream.
 *
 * \param[in]   pFlux
 * \param[in]   pV
 * \return      std::ostream&
 */
std::ostream& operator<<(std::ostream& pFlux, const Vector3& pV);

/**
 * \fn      operator==
 * \brief   Equal operator.
 *
 * \param[in]   pA
 * \param[in]   pB
 * \return      const bool		true if pA and pB are equal, false otherwise
 */
const bool operator==(const Vector3& pA, const Vector3& pB);

/**
 * \fn      operator!=
 * \brief   Not equal operator.
 *
 * \param[in]   pA
 * \param[in]   pB
 * \return      const bool		false if pA and pB are equal, true otherwise
 */
const bool operator!=(const Vector3& pA, const Vector3& pB);

/**
 * \fn      operator+
 * \brief   Element wise addition between two Vector3.
 *
 * \param[in]   pA
 * \param[in]   pB
 * \return      Vector3
 */
Vector3 operator+(const Vector3& pA, const Vector3& pB);

/**
 * \fn      operator-
 * \brief   Element wise substraction between two Vector3.
 *
 * \param[in]   pA
 * \param[in]   pB
 * \return      Vector3
 */
Vector3 operator-(const Vector3& pA, const Vector3& pB);

/**
 * \fn      operator*
 * \brief   Multiply a Vector3 by a scalar
 *
 * \param[in]   pA
 * \param[in]   pScalar
 * \return      Vector3
 */
Vector3 operator*(const Vector3& pA, double pScalar);

/**
 * \fn      operator/
 * \brief   Divides a Vector3 by a scalar
 *
 * \param[in]   pA
 * \param[in]   pScalar
 * \return      Vector3
 */
Vector3 operator/(const Vector3& pA, double pScalar);

/**
 * \fn      operator*
 * \brief   Dot product between two Vector3
 *
 * \param[in]   pA
 * \param[in]   pB
 * \return      double
 */
double operator*(const Vector3& pA, const Vector3& pB);