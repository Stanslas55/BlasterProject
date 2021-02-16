#include "Matrix4.hpp"

Matrix4::Matrix4() {
	m_matrix[0] = &m_data[0];
	m_matrix[1] = &m_data[4];
	m_matrix[2] = &m_data[8];
	m_matrix[3] = &m_data[12];
}

Matrix4::Matrix4(const Matrix4& pCopy) {
	m_data[0] = pCopy.m_data[0];
	m_data[1] = pCopy.m_data[1];
	m_data[2] = pCopy.m_data[2];
	m_data[3] = pCopy.m_data[3];
	m_data[4] = pCopy.m_data[4];
	m_data[5] = pCopy.m_data[5];
	m_data[6] = pCopy.m_data[6];
	m_data[7] = pCopy.m_data[7];
	m_data[8] = pCopy.m_data[8];
	m_data[9] = pCopy.m_data[9];
	m_data[10] = pCopy.m_data[10];
	m_data[11] = pCopy.m_data[11];
	m_data[12] = pCopy.m_data[12];
	m_data[13] = pCopy.m_data[13];
	m_data[14] = pCopy.m_data[14];
	m_data[15] = pCopy.m_data[15];

	m_matrix[0] = &m_data[0];
	m_matrix[1] = &m_data[4];
	m_matrix[2] = &m_data[8];
	m_matrix[3] = &m_data[12];
}

Matrix4& Matrix4::operator=(const Matrix4& M)
{
    for (size_t Row = 0; Row < 4; Row++)
    {
        for (size_t Col = 0; Col < 4; Col++)
        {
            m_matrix[Row][Col] = M[Row][Col];
        }
    }
    return (*this);
}

double Matrix4::determinant() const {
    //
    // Inversion by Cramer's rule.  Code taken from an Intel publication
    //
    double result[4][4];
    double tmp[12]; /* temp array for pairs */
    double src[16]; /* array of transpose source matrix */

    /* transpose matrix */
    for (size_t i = 0; i < 4; i++)
    {
        src[i + 0] = (*this)[i][0];
        src[i + 4] = (*this)[i][1];
        src[i + 8] = (*this)[i][2];
        src[i + 12] = (*this)[i][3];
    }
    /* calculate pairs for first 8 elements (cofactors) */
    tmp[0] = src[10] * src[15];
    tmp[1] = src[11] * src[14];
    tmp[2] = src[9] * src[15];
    tmp[3] = src[11] * src[13];
    tmp[4] = src[9] * src[14];
    tmp[5] = src[10] * src[13];
    tmp[6] = src[8] * src[15];
    tmp[7] = src[11] * src[12];
    tmp[8] = src[8] * src[14];
    tmp[9] = src[10] * src[12];
    tmp[10] = src[8] * src[13];
    tmp[11] = src[9] * src[12];
    /* calculate first 8 elements (cofactors) */
    result[0][0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
    result[0][0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
    result[0][1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
    result[0][1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
    result[0][2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
    result[0][2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
    result[0][3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
    result[0][3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
    result[1][0] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
    result[1][0] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
    result[1][1] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
    result[1][1] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
    result[1][2] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
    result[1][2] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
    result[1][3] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
    result[1][3] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];
    /* calculate pairs for second 8 elements (cofactors) */
    tmp[0] = src[2] * src[7];
    tmp[1] = src[3] * src[6];
    tmp[2] = src[1] * src[7];
    tmp[3] = src[3] * src[5];
    tmp[4] = src[1] * src[6];
    tmp[5] = src[2] * src[5];

    tmp[6] = src[0] * src[7];
    tmp[7] = src[3] * src[4];
    tmp[8] = src[0] * src[6];
    tmp[9] = src[2] * src[4];
    tmp[10] = src[0] * src[5];
    tmp[11] = src[1] * src[4];
    /* calculate second 8 elements (cofactors) */
    result[2][0] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
    result[2][0] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
    result[2][1] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
    result[2][1] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
    result[2][2] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
    result[2][2] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
    result[2][3] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
    result[2][3] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
    result[3][0] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
    result[3][0] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
    result[3][1] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
    result[3][1] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
    result[3][2] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
    result[3][2] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
    result[3][3] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
    result[3][3] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];
    /* calculate determinant */
    return src[0] * result[0][0] + src[1] * result[0][1] + src[2] * result[0][2] + src[3] * result[0][3];
}

Matrix4 Matrix4::transpose() const {

    Matrix4 result;
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t i2 = 0; i2 < 4; i2++)
        {
            result[i2][i] = m_matrix[i][i2];
        }
    }
    return result;
}

Matrix4 Matrix4::inverse() const
{
    //
    // Inversion by Cramer's rule.  Code taken from an Intel publication
    //
    Matrix4 result;
    double tmp[12]; /* temp array for pairs */
    double src[16]; /* array of transpose source matrix */
    double det; /* determinant */
    /* transpose matrix */
    for (size_t i = 0; i < 4; i++)
    {
        src[i + 0] = (*this)[i][0];
        src[i + 4] = (*this)[i][1];
        src[i + 8] = (*this)[i][2];
        src[i + 12] = (*this)[i][3];
    }
    /* calculate pairs for first 8 elements (cofactors) */
    tmp[0] = src[10] * src[15];
    tmp[1] = src[11] * src[14];
    tmp[2] = src[9] * src[15];
    tmp[3] = src[11] * src[13];
    tmp[4] = src[9] * src[14];
    tmp[5] = src[10] * src[13];
    tmp[6] = src[8] * src[15];
    tmp[7] = src[11] * src[12];
    tmp[8] = src[8] * src[14];
    tmp[9] = src[10] * src[12];
    tmp[10] = src[8] * src[13];
    tmp[11] = src[9] * src[12];
    /* calculate first 8 elements (cofactors) */
    result[0][0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
    result[0][0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
    result[0][1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
    result[0][1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
    result[0][2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
    result[0][2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
    result[0][3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
    result[0][3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
    result[1][0] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
    result[1][0] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
    result[1][1] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
    result[1][1] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
    result[1][2] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
    result[1][2] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
    result[1][3] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
    result[1][3] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];
    /* calculate pairs for second 8 elements (cofactors) */
    tmp[0] = src[2] * src[7];
    tmp[1] = src[3] * src[6];
    tmp[2] = src[1] * src[7];
    tmp[3] = src[3] * src[5];
    tmp[4] = src[1] * src[6];
    tmp[5] = src[2] * src[5];

    tmp[6] = src[0] * src[7];
    tmp[7] = src[3] * src[4];
    tmp[8] = src[0] * src[6];
    tmp[9] = src[2] * src[4];
    tmp[10] = src[0] * src[5];
    tmp[11] = src[1] * src[4];
    /* calculate second 8 elements (cofactors) */
    result[2][0] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
    result[2][0] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
    result[2][1] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
    result[2][1] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
    result[2][2] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
    result[2][2] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
    result[2][3] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
    result[2][3] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
    result[3][0] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
    result[3][0] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
    result[3][1] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
    result[3][1] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
    result[3][2] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
    result[3][2] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
    result[3][3] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
    result[3][3] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];
    /* calculate determinant */
    det = src[0] * result[0][0] + src[1] * result[0][1] + src[2] * result[0][2] + src[3] * result[0][3];
    /* calculate matrix inverse */
    det = 1.0 / det;

    return result * det;
}

void Matrix4::fill(const double pScalar) {
    m_data[0] = pScalar;
    m_data[1] = pScalar;
    m_data[2] = pScalar;
    m_data[3] = pScalar;
    m_data[4] = pScalar;
    m_data[5] = pScalar;
    m_data[6] = pScalar;
    m_data[7] = pScalar;
    m_data[8] = pScalar;
    m_data[9] = pScalar;
    m_data[10] = pScalar;
    m_data[11] = pScalar;
    m_data[12] = pScalar;
    m_data[13] = pScalar;
    m_data[14] = pScalar;
    m_data[15] = pScalar;
}

std::ostream& operator<<(std::ostream& pFlux, Matrix4 pV) {
    pFlux << "["
        << pV[0][0] << ", " << pV[0][1] << ", " << pV[0][2] << ", " << pV[0][3] << std::endl
        << pV[1][0] << ", " << pV[1][1] << ", " << pV[1][2] << ", " << pV[1][3] << std::endl
        << pV[2][0] << ", " << pV[2][1] << ", " << pV[2][2] << ", " << pV[2][3] << std::endl
        << pV[3][0] << ", " << pV[3][1] << ", " << pV[3][2] << ", " << pV[3][3] << "]";

    return pFlux;
}

const bool operator==(const Matrix4& pA, const Matrix4& pB) {
    return pA[0][0] == pB[0][0] &&
        pA[0][1] == pB[0][1] &&
        pA[0][2] == pB[0][2] &&
        pA[0][3] == pB[0][3] &&
        pA[1][0] == pB[1][0] &&
        pA[1][1] == pB[1][1] &&
        pA[1][2] == pB[1][2] &&
        pA[1][3] == pB[1][3] &&
        pA[2][0] == pB[2][0] &&
        pA[2][1] == pB[2][1] &&
        pA[2][2] == pB[2][2] &&
        pA[2][3] == pB[2][3] &&
        pA[3][0] == pB[3][0] &&
        pA[3][1] == pB[3][1] &&
        pA[3][2] == pB[3][2] &&
        pA[3][3] == pB[3][3];
}

Matrix4 operator+(Matrix4 pA, Matrix4 pB) {
    Matrix4 res;

    res[0][0] = pA[0][0] + pB[0][0];
    res[0][1] = pA[0][1] + pB[0][1];
    res[0][2] = pA[0][2] + pB[0][2];
    res[0][3] = pA[0][3] + pB[0][3];
    res[1][0] = pA[1][0] + pB[1][0];
    res[1][1] = pA[1][1] + pB[1][1];
    res[1][2] = pA[1][2] + pB[1][2];
    res[1][3] = pA[1][3] + pB[1][3];
    res[2][0] = pA[2][0] + pB[2][0];
    res[2][1] = pA[2][1] + pB[2][1];
    res[2][2] = pA[2][2] + pB[2][2];
    res[2][3] = pA[2][3] + pB[2][3];
    res[3][0] = pA[3][0] + pB[3][0];
    res[3][1] = pA[3][1] + pB[3][1];
    res[3][2] = pA[3][2] + pB[3][2];
    res[3][3] = pA[3][3] + pB[3][3];
    
    return res;
}

Matrix4 operator-(Matrix4 pA, Matrix4 pB) {
    Matrix4 res;

    res[0][0] = pA[0][0] - pB[0][0];
    res[0][1] = pA[0][1] - pB[0][1];
    res[0][2] = pA[0][2] - pB[0][2];
    res[0][3] = pA[0][3] - pB[0][3];
    res[1][0] = pA[1][0] - pB[1][0];
    res[1][1] = pA[1][1] - pB[1][1];
    res[1][2] = pA[1][2] - pB[1][2];
    res[1][3] = pA[1][3] - pB[1][3];
    res[2][0] = pA[2][0] - pB[2][0];
    res[2][1] = pA[2][1] - pB[2][1];
    res[2][2] = pA[2][2] - pB[2][2];
    res[2][3] = pA[2][3] - pB[2][3];
    res[3][0] = pA[3][0] - pB[3][0];
    res[3][1] = pA[3][1] - pB[3][1];
    res[3][2] = pA[3][2] - pB[3][2];
    res[3][3] = pA[3][3] - pB[3][3];

    return res;
}

Matrix4 operator+(Matrix4 pA, double pScalar) {
    Matrix4 res;

    res[0][0] = pA[0][0] + pScalar;
    res[0][1] = pA[0][1] + pScalar;
    res[0][2] = pA[0][2] + pScalar;
    res[0][3] = pA[0][3] + pScalar;
    res[1][0] = pA[1][0] + pScalar;
    res[1][1] = pA[1][1] + pScalar;
    res[1][2] = pA[1][2] + pScalar;
    res[1][3] = pA[1][3] + pScalar;
    res[2][0] = pA[2][0] + pScalar;
    res[2][1] = pA[2][1] + pScalar;
    res[2][2] = pA[2][2] + pScalar;
    res[2][3] = pA[2][3] + pScalar;
    res[3][0] = pA[3][0] + pScalar;
    res[3][1] = pA[3][1] + pScalar;
    res[3][2] = pA[3][2] + pScalar;
    res[3][3] = pA[3][3] + pScalar;

    return res;
}

Matrix4 operator-(Matrix4 pA, double pScalar) {
    Matrix4 res;

    res[0][0] = pA[0][0] - pScalar;
    res[0][1] = pA[0][1] - pScalar;
    res[0][2] = pA[0][2] - pScalar;
    res[0][3] = pA[0][3] - pScalar;
    res[1][0] = pA[1][0] - pScalar;
    res[1][1] = pA[1][1] - pScalar;
    res[1][2] = pA[1][2] - pScalar;
    res[1][3] = pA[1][3] - pScalar;
    res[2][0] = pA[2][0] - pScalar;
    res[2][1] = pA[2][1] - pScalar;
    res[2][2] = pA[2][2] - pScalar;
    res[2][3] = pA[2][3] - pScalar;
    res[3][0] = pA[3][0] - pScalar;
    res[3][1] = pA[3][1] - pScalar;
    res[3][2] = pA[3][2] - pScalar;
    res[3][3] = pA[3][3] - pScalar;

    return res;
}

Matrix4 operator*(Matrix4 pA, double pScalar) {
    Matrix4 res;

    res[0][0] = pA[0][0] * pScalar;
    res[0][1] = pA[0][1] * pScalar;
    res[0][2] = pA[0][2] * pScalar;
    res[0][3] = pA[0][3] * pScalar;
    res[1][0] = pA[1][0] * pScalar;
    res[1][1] = pA[1][1] * pScalar;
    res[1][2] = pA[1][2] * pScalar;
    res[1][3] = pA[1][3] * pScalar;
    res[2][0] = pA[2][0] * pScalar;
    res[2][1] = pA[2][1] * pScalar;
    res[2][2] = pA[2][2] * pScalar;
    res[2][3] = pA[2][3] * pScalar;
    res[3][0] = pA[3][0] * pScalar;
    res[3][1] = pA[3][1] * pScalar;
    res[3][2] = pA[3][2] * pScalar;
    res[3][3] = pA[3][3] * pScalar;

    return res;
}

Matrix4 operator/(Matrix4 pA, double pScalar) {
    Matrix4 res;

    if (pScalar == 0) {
        res.fill(NAN);
        return res;
    }

    res[0][0] = pA[0][0] / pScalar;
    res[0][1] = pA[0][1] / pScalar;
    res[0][2] = pA[0][2] / pScalar;
    res[0][3] = pA[0][3] / pScalar;
    res[1][0] = pA[1][0] / pScalar;
    res[1][1] = pA[1][1] / pScalar;
    res[1][2] = pA[1][2] / pScalar;
    res[1][3] = pA[1][3] / pScalar;
    res[2][0] = pA[2][0] / pScalar;
    res[2][1] = pA[2][1] / pScalar;
    res[2][2] = pA[2][2] / pScalar;
    res[2][3] = pA[2][3] / pScalar;
    res[3][0] = pA[3][0] / pScalar;
    res[3][1] = pA[3][1] / pScalar;
    res[3][2] = pA[3][2] / pScalar;
    res[3][3] = pA[3][3] / pScalar;

    return res;
}

Matrix4 operator*(Matrix4 pA, Matrix4 pB) {
    return pA;
}