#pragma once

#include "../Vector3/Vector3.hpp"

/**
* \class Matrix4
* \brief Utility class for 3D transformations
*/
class Matrix4 {

private:

	double m_data[16] = {	
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};

	double* m_matrix[4];

public:

	/**
	* \fn Matrix4
	* \brief Default Constructor. Initialize an Identity Matrixs
	*/
	Matrix4();

	/**
	* \fn Matrix4
	* \brief Camera copy Constructor
	*
	* \param	pCopy		Matrix4 object to copy
	*/
	Matrix4(const Matrix4& pCopy);

	/**
	* \fn operator=
	* \brief Assignement operator
	*
	* \param	pM			Matrix4 object to assign
	* 
	* \return	Matrix4&	reference to this Matrix4
	*/
	Matrix4& operator=(const Matrix4& pM);

	/**
	* \fn operator[]
	* \brief Accessor operator
	*
	* \param	pRow	Row to access
	*
	* \return	float*	address of the pRow-th row
	*/
	inline double* operator [] (int pRow) { return m_matrix[pRow]; }

	/**
	* \fn operator[]
	* \brief Const accessor operator
	*
	* \param	pRow	Row to access
	*
	* \return	float*	address of the pRow-th row
	*/
	inline const double* operator [] (int pRow) const  { return m_matrix[pRow]; }

	/**
	* \fn determinant
	* \brief Compute the determinant of this Matrix4
	* 
	* \return float		determinant of this Matrix4
	*/
	double determinant() const;

	/**
	* \fn transpose
	* \brief Transposes a copy of this Matrix
	*
	* \return Matrix4	Transposed Matrix4 from this
	*/
	Matrix4 transpose() const;

	/**
	* \fn invers
	* \brief Inverse a copy of this Matrix
	*
	* \return Matrix4	Inversed Matrix4 from this
	*/

	Matrix4 inverse() const;

	/**
	 * \fn      fill
	 * \brief   Fill this matrix with a scalar.
	 * 
	 * \param   pScalar
	 */
	void fill(const double pScalar);
};

std::ostream& operator<<(std::ostream& pFlux, Matrix4 pV);

const bool operator==(const Matrix4& pA, const Matrix4& pB);

Matrix4 operator+(Matrix4 pA, Matrix4 pB);
Matrix4 operator-(Matrix4 pA, Matrix4 pB);

Matrix4 operator*(Matrix4 pA, Matrix4 pB);

Matrix4 operator+(Matrix4 pA, double pScalar);
Matrix4 operator-(Matrix4 pA, double pScalar);
Matrix4 operator*(Matrix4 pA, double pScalar);
Matrix4 operator/(Matrix4 pA, double pScalar);