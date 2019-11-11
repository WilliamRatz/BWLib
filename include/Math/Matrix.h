//
//  Matrix.h
//  BWLib
//
//  Created by William Ratz on 11.04.19
//  Copyright © 2019 William Ratz. All rights reserved.
//

#ifndef Matrix_H
#define Matrix_H
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"


//#define MatrixTemplate template<typename T, std::size_t R, std::size_t C>
//#define MatrixMacro Matrix<T, R, C, typename std::enable_if<std::is_same<T, double>::value || std::is_same<T, float>::value>>


template<typename T, std::size_t R, std::size_t C>
class MatrixMacro {
private:
	Vector<T, C> m_mat[R];

public:
	inline Matrix()
	{
		this->identity();
	}
	inline Matrix(const Matrix& mat)
	{
		*this = mat;
	}
	inline ~Matrix() {};

	Vector<T, C>& operator[](const std::size_t index) {
		if (index >= R) {
			throw std::out_of_range("Index out of Range");
		}
		return m_mat[index];
	}

#pragma region methods
	inline Vector3 Forward()
	{
		return Vector3(m_mat[0][2], m_mat[1][2], m_mat[2][2]);
	}
	inline Vector3 Backwards()
	{
		return Vector3(-m_mat[0][2], -m_mat[1][2], -m_mat[2][2]);
	}
	inline Vector3 Left()
	{
		return Vector3(-m_mat[0][0], -m_mat[1][0], -m_mat[2][0]);
	}
	inline Vector3 Right()
	{
		return Vector3(m_mat[0][0], m_mat[1][0], m_mat[2][0]);
	}
	inline Vector3 Up()
	{
		return Vector3(m_mat[0][1], m_mat[1][1], m_mat[2][1]);
	}
	inline Vector3 Down()
	{
		return Vector3(-m_mat[0][1], -m_mat[1][1], -m_mat[2][1]);
	}

	inline double Yaw()
	{
		return (m_mat[0][0] == (T)1 || m_mat[0][0] == (T)-1) ? std::atan2f(m_mat[0][2], m_mat[2][3]) : std::atan2f(-m_mat[2][0], m_mat[0][0]);
	}
	inline double Pitch()
	{
		return (m_mat[0][0] == (T)1 || m_mat[0][0] == (T)-1) ? 0 : std::asin(m_mat[1][0]);
	}
	inline double Roll()
	{
		return (m_mat[0][0] == (T)1 || m_mat[0][0] == (T)-1) ? 0 : std::atan2(-m_mat[1][2], m_mat[1][1]);
	}

	inline std::size_t getHashCode()
	{
		long long hash = m_mat[0][0];

		for (long long i = 0; i < R; ++i) {
			for (long long ii = 0; ii < C; ++ii) {
				hash = (hash * 397) ^ static_cast<long long>(m_mat[i][ii]);
			}
		}

		return hash;
	}
	inline std::size_t countColumns()
	{
		return C;
	}
	inline std::size_t countRows()
	{
		return R;
	}

	inline Matrix& translate2D(float p_x, float p_y)
	{
		if (R < 3 && C < 2) {
			throw std::out_of_range("Your Matrix don't fit for 2D translation check your dimensions");
		}

		MatrixMacro trans2D;

		trans2D[0][2] = (T)p_x;
		trans2D[1][2] = (T)p_y;

		*this *= trans2D;

		return *this;
	}
	inline Matrix& scale2D(float p_widthHeight)
	{
		if (R < 2 && C < 2) {
			throw std::out_of_range("Your Matrix dont fit for 2D scaleing, check your dimensions");
		}

		Matrix scal2D;

		scal2D[0][2] = (T)p_widthHeight;
		scal2D[1][2] = (T)p_widthHeight;

		*this *= scal2D;

		return *this;
	}
	inline Matrix& scale2D(float p_width, float p_height)
	{
		if (R < 2 && C < 2) {
			throw std::out_of_range("Your Matrix dont fit for 2D scaleing, check your dimensions");
		}

		Matrix scal2D;

		scal2D[0][2] = (T)p_width;
		scal2D[1][2] = (T)p_height;

		*this *= scal2D;

		return *this;
	}
	inline Matrix& scale2D(Vector2 p_vec2)
	{
		if (R < 2 && C < 2) {
			throw std::out_of_range("Your Matrix dont fit for 2D scaleing, check your dimensions");
		}

		Matrix scal2D;

		scal2D[0][2] = (T)p_vec2.x();
		scal2D[1][2] = (T)p_vec2.y();

		*this *= scal2D;

		return *this;
	}
	inline Matrix& rotation2D(float p_angle)
	{
		if (R < 2 && C < 2) {
			throw std::out_of_range("Your Matrix dont fit for 2D rotation, check your dimensions");
		}

		Matrix rotat2D;
		double degress = (double)p_angle * BWMath::PI / 180; // change from Rad to degrees

		rotat2D[0][0] = (T)std::cos(degress);
		rotat2D[0][1] = (T)std::sin(degress);
		rotat2D[1][0] = (T)-std::sin(degress);
		rotat2D[1][1] = (T)std::cos(degress);

		*this *= rotat2D;
		return *this;
	}

	inline Matrix& translate3D(float p_x, float p_y, float p_z)
	{
		if (R < 4 && C < 3) {
			throw std::out_of_range("Your Matrix dont fit for 3D translation, check your dimensions");
		}

		Matrix trans3D;

		trans3D[0][3] = (T)p_x;
		trans3D[1][3] = (T)p_y;
		trans3D[2][3] = (T)p_z;

		*this *= trans3D;
		return *this;
	}
	inline Matrix& translate3D(Vector3 p_vec3)
	{
		if (R < 4 && C < 3) {
			throw std::out_of_range("Your Matrix dont fit for 3D translation, check your dimensions");
		}

		Matrix trans3D;

		trans3D[0][3] = (T)p_vec3.x();
		trans3D[1][3] = (T)p_vec3.y();
		trans3D[2][3] = (T)p_vec3.z();

		*this *= trans3D;
		return *this;
	}
	inline Matrix& scale3D(float p_widthHeightDepth)
	{
		if (R < 3 && C < 3) {
			throw std::out_of_range("Your Matrix dont fit for 3D scaleing, check your dimensions");
		}

		Matrix scal3D;

		scal3D[0][0] = (T)p_widthHeightDepth;
		scal3D[1][1] = (T)p_widthHeightDepth;
		scal3D[2][2] = (T)p_widthHeightDepth;

		*this *= scal3D;
		return *this;
	}
	inline Matrix& scale3D(float p_width, float p_height, float p_depth)
	{
		if (R < 3 && C < 3) {
			throw std::out_of_range("Your Matrix dont fit for 3D scaleing, check your dimensions");
		}

		Matrix scal3D;

		scal3D[0][0] = (T)p_width;
		scal3D[1][1] = (T)p_height;
		scal3D[2][2] = (T)p_depth;

		*this *= scal3D;
		return *this;
	}
	inline Matrix& scale3D(Vector3 p_vec3)
	{
		if (R < 3 && C < 3) {
			throw std::out_of_range("Your Matrix dont fit for 3D scaleing, check your dimensions");
		}

		Matrix scal3D;

		scal3D[0][0] = (T)p_vec3.x();
		scal3D[1][1] = (T)p_vec3.y();
		scal3D[2][2] = (T)p_vec3.z();

		*this *= scal3D;
		return *this;
	}
	inline Matrix& rotation3DAroundX(float p_angle)
	{
		if (R < 3 && C < 3) {
			throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"X\", check your dimensions");
		}

		Matrix rotat3DX;
		double degress = (double)p_angle * BWMath::PI / 180; // change from Rad to degrees

		rotat3DX[1][1] = (T)std::cos(degress);
		rotat3DX[1][2] = (T)-std::sin(degress);
		rotat3DX[2][1] = (T)std::sin(degress);
		rotat3DX[2][2] = (T)std::cos(degress);

		this->operator*=(rotat3DX);
		return *this;
	}
	inline Matrix& rotation3DAroundY(float p_angle)
	{
		if (R < 3 && C < 3) {
			throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"Y\", check your dimensions");
		}

		Matrix rotat3DY;
		double degress = (double)p_angle * BWMath::PI / 180; // change from Rad to degrees

		rotat3DY[0][0] = (T)std::cos(degress);
		rotat3DY[0][2] = (T)std::sin(degress);
		rotat3DY[2][0] = (T)-std::sin(degress);
		rotat3DY[2][2] = (T)std::cos(degress);

		this->operator*=(rotat3DY);
		return *this;
	}
	inline Matrix& rotation3DAroundZ(float p_angle)
	{
		if (R < 3 && C < 3) {
			throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"Z\", check your dimensions");
		}

		Matrix rotat3DZ;
		double degress = (double)p_angle * BWMath::PI / 180; // change from Rad to degrees

		rotat3DZ[0][0] = (T)std::cos(degress);
		rotat3DZ[0][1] = (T)-std::sin(degress);
		rotat3DZ[1][0] = (T)std::sin(degress);
		rotat3DZ[1][1] = (T)std::cos(degress);

		this->operator*=(rotat3DZ);
		return *this;
	}

	inline Matrix& rotation3DAroundXlocal(float p_angle)
	{
		if (R < 3 && C < 3) {
			throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"X\", check your dimensions");
		}
		Vector3 transformation(m_mat[0][3], m_mat[1][3], m_mat[2][3]);

		this->m_mat[0][3] = 0;
		this->m_mat[1][3] = 0;
		this->m_mat[2][3] = 0;

		this->rotation3DAroundX(p_angle);

		this->m_mat[0][3] = transformation.x();
		this->m_mat[1][3] = transformation.y();
		this->m_mat[2][3] = transformation.z();

		return *this;
	}
	inline Matrix& rotation3DAroundYlocal(float p_angle)
	{
		if (R < 3 && C < 3) {
			throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"Y\", check your dimensions");
		}

		Vector3 transformation(m_mat[0][3], m_mat[1][3], m_mat[2][3]);

		this->m_mat[0][3] = 0;
		this->m_mat[1][3] = 0;
		this->m_mat[2][3] = 0;

		this->rotation3DAroundY(p_angle);

		this->m_mat[0][3] = transformation.x();
		this->m_mat[1][3] = transformation.y();
		this->m_mat[2][3] = transformation.z();

		return *this;
	}
	inline Matrix& rotation3DAroundZlocal(float p_angle)
	{
		if (R < 3 && C < 3) {
			throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"Z\", check your dimensions");
		}

		Vector3 transformation(m_mat[0][3], m_mat[1][3], m_mat[2][3]);

		this->m_mat[0][3] = 0;
		this->m_mat[1][3] = 0;
		this->m_mat[2][3] = 0;

		this->rotation3DAroundZ(p_angle);

		this->m_mat[0][3] = transformation.x();
		this->m_mat[1][3] = transformation.y();
		this->m_mat[2][3] = transformation.z();

		return *this;

	}

	inline Matrix& rotation3DAroundArbitararyAxis(float angle, Vector3 axis)
	{
		if (R < 3 && C < 3) {
			throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"Z\", check your dimensions");
		}

		double degress = (double)angle * BWMath::PI / 180; // change from Rad to degrees

		axis.normalize();

		Matrix rotat3DArbiAxis;

		rotat3DArbiAxis[0][0] = (axis.x() * axis.x()) + ((axis.y() * axis.y()) + (axis.z() * axis.z())) * std::cos(degress);
		rotat3DArbiAxis[0][1] = axis.x() * axis.y() * (1 - std::cos(degress)) - axis.z() * std::sin(degress);
		rotat3DArbiAxis[0][2] = axis.x() * axis.z() * (1 - std::cos(degress)) + axis.y() * std::sin(degress);
		rotat3DArbiAxis[0][3] = (m_mat[0][3] * ((axis.y() * axis.y()) + (axis.z() * axis.z())) - axis.x() * (m_mat[1][3] * axis.y() + m_mat[2][3] * axis.z())) * (1 - std::cos(degress)) + (m_mat[1][3] * axis.z() - m_mat[2][3] * axis.y()) * std::sin(degress);
		rotat3DArbiAxis[1][0] = axis.x() * axis.y() * (1 - std::cos(degress)) + axis.z() * std::sin(degress);
		rotat3DArbiAxis[1][1] = (axis.y() * axis.y()) + ((axis.x() * axis.x()) + (axis.z() * axis.z())) * std::cos(degress);
		rotat3DArbiAxis[1][2] = axis.y() * axis.z() * (1 - std::cos(degress)) - axis.x() * std::sin(degress);
		rotat3DArbiAxis[1][3] = (m_mat[1][3] * ((axis.x() * axis.x()) + (axis.z() * axis.z())) - axis.y() * (m_mat[0][3] * axis.x() + m_mat[2][3] * axis.z())) * (1 - std::cos(degress)) + (m_mat[2][3] * axis.x() - m_mat[0][3] * axis.z()) * std::sin(degress);
		rotat3DArbiAxis[2][0] = axis.x() * axis.z() * (1 - std::cos(degress)) - axis.y() * std::sin(degress);
		rotat3DArbiAxis[2][1] = axis.y() * axis.z() * (1 - std::cos(degress)) + axis.x() * std::sin(degress);
		rotat3DArbiAxis[2][2] = (axis.z() * axis.z()) + ((axis.x() * axis.x()) + (axis.y() * axis.y())) * std::cos(degress);
		rotat3DArbiAxis[2][3] = (m_mat[2][3] * ((axis.x() * axis.x()) + (axis.y() * axis.y())) - axis.z() * (m_mat[0][3] * axis.x() + m_mat[1][3] * axis.y())) * (1 - std::cos(degress)) + (m_mat[0][3] * axis.y() - m_mat[1][3] * axis.x()) * std::sin(degress);
		this->operator*=(rotat3DArbiAxis);
		return *this;

	}

	inline Matrix& perspectivProjection(float p_windowWidth, float p_windowHeight, float p_nearPlane, float p_farPlane)
	{
		if (R < 4 && C < 4) {
			throw std::out_of_range("Your Matrix dont fit for perspectiv projection, check your dimensions");
		}

		Matrix perProj;

		perProj[0][0] = (T)((2 * p_nearPlane) / p_windowWidth);
		perProj[1][1] = (T)((2 * p_nearPlane) / p_windowHeight);
		perProj[2][2] = (T)(p_farPlane / (p_farPlane - p_nearPlane));
		perProj[2][3] = (T)1;
		perProj[3][2] = (T)((-p_farPlane * p_nearPlane) / (p_farPlane - p_nearPlane));
		perProj[3][3] = 0;
		*this = perProj;
		return *this;
	}
	inline Matrix& orthogonalProjection(float p_windowWidth, float p_windowHeight, float p_nearPlane, float p_farPlane)
	{
		if (R < 4 && C < 3) {
			throw std::out_of_range("Your Matrix dont fit for orthogonal projection, check your dimensions");
		}

		Matrix perProj;

		perProj[0][0] = (T)(2 / p_windowWidth);
		perProj[1][1] = (T)(2 / p_windowHeight);
		perProj[2][2] = (T)(1 / (p_farPlane - p_nearPlane));
		perProj[3][3] = (T)(-p_nearPlane / (p_farPlane - p_nearPlane));

		if (C > 3)
		{
			perProj[3][3] = (T)1;
		}

		*this = perProj;
		return *this;
	}

	inline Vector3 getScale()
	{
		return Vector3(m_mat[0][0], m_mat[1][1], m_mat[2][2]);
	}
	inline Vector3 getTransform()
	{
		return Vector3(m_mat[0][3], m_mat[1][3], m_mat[2][3]);
	}

	inline Matrix& zero() {

		for (std::size_t i = 0; i < C; ++i) {
			for (std::size_t ii = 0; ii < R; ++ii) {
				m_mat[ii][i] = T(0);
			}
		}
		return *this;

	}
	inline Matrix& identity() {

		for (std::size_t i = 0; i < C; ++i) {
			for (std::size_t ii = 0; ii < R; ++ii) {
				m_mat[ii][i] = (i == ii) ? T(1) : T(0);
			}
		}
		return *this;

	}
	inline Matrix& inverse()
	{
		Matrix<T, R, C * 2> tempMat;
		float temp;


		for (std::size_t i = 0; i < C; ++i) {
			for (std::size_t ii = 0; ii < R; ++ii) {
				tempMat[ii][i] = m_mat[ii][i];
			}
		}


		for (int i = 0; i < R; i++) {

			for (int j = 0; j < 2 * R; j++) {
				if (j == (i + R))
					tempMat[i][j] = 1;
			}
		}

		for (int i = R - 1; i > 0; i--) {

			if (tempMat[i - 1][0] < tempMat[i][0])
				for (int j = 0; j < 2 * R; j++) {
					temp = tempMat[i][j];
					tempMat[i][j] = tempMat[i - 1][j];
					tempMat[i - 1][j] = temp;
				}
		}

		for (int i = 0; i < R; i++) {

			for (int j = 0; j < R; j++) {

				if (j != i) {

					temp = tempMat[j][i] / tempMat[i][i];
					for (int k = 0; k < 2 * R; k++) {
						tempMat[j][k] -= tempMat[i][k] * temp;
					}
				}
			}
		}

		for (int i = 0; i < R; i++) {

			temp = tempMat[i][i];
			for (int j = 0; j < 2 * R; j++) {

				tempMat[i][j] = tempMat[i][j] / temp;
			}
		}


		for (std::size_t i = C; i < C * 2; ++i) {
			for (std::size_t ii = 0; ii < R; ++ii) {
				m_mat[ii][i - C] = tempMat[ii][i];
			}
		}

		std::cout << *this << std::endl;

		return *this;
	}
	inline Matrix<T, C, R> transpose()
	{
		Matrix<T, C, R> temp;

		for (std::size_t i = 0; i < C; ++i) {
			for (std::size_t ii = 0; ii < R; ++ii) {
				temp[i][ii] = m_mat[ii][i];
			}
		}

		return temp;
	}
#pragma endregion

#pragma region arithmeticOperations
	 inline void operator=(const Matrix& p_mat)
	{
		for (std::size_t i = 0; i < C; ++i) {
			for (std::size_t ii = 0; ii < R; ++ii) {
				m_mat[ii][i] = p_mat.m_mat[ii][i];
			}
		}
	}
	 inline Matrix operator-()
	{
		for (std::size_t i = 0; i < C; ++i) {
			for (std::size_t ii = 0; ii < R; ++ii) {
				m_mat[ii][i] = -m_mat[ii][i];
			}
		}

		return *this;
	}
	 inline Matrix operator+(const Matrix& p_mat) {

		Matrix temp(*this);
		return temp += p_mat;
	}
	 inline Matrix operator-(const Matrix& p_mat) {

		Matrix temp(*this);
		return temp -= p_mat;
	}
	 inline Matrix operator*(const Matrix& p_mat) {

		Matrix temp(*this);
		return temp *= p_mat;
	}

	 inline Matrix& operator+=(const Matrix& p_mat)
	{
		for (std::size_t i = 0; i < R; ++i) {
			for (std::size_t ii = 0; ii < C; ++ii) {
				m_mat[i][ii] = m_mat[i][ii] + p_mat.m_mat[i][ii];
			}
		}
		return *this;
	}
	 inline Matrix& operator-=(const Matrix& p_mat)
	{
		for (std::size_t i = 0; i < R; ++i) {
			for (std::size_t ii = 0; ii < C; ++ii) {
				m_mat[i][ii] = m_mat[i][ii] - p_mat.m_mat[i][ii];
			}
		}
		return *this;
	}
	 inline Matrix& operator*=(const Matrix& p_mat)
	{
		T tempValue = (T)0;
		Matrix<T, R, R> tempMat;

		for (std::size_t i = 0; i < R; ++i) {
			for (std::size_t ii = 0; ii < R; ++ii) {
				for (std::size_t iii = 0; iii < C; ++iii) {
					tempValue += m_mat[i][iii] * p_mat.m_mat[iii][ii];
				}
				tempMat[i][ii] = tempValue;
				tempValue = (T)0;
			}
		}
		*this = tempMat;
		return *this;
	}
#pragma endregion

#pragma region comparisonOperations
	 inline bool operator==(Matrix& p_mat)
	{
		for (std::size_t i = 0; i < R; ++i) {
			for (std::size_t ii = 0; ii < C; ++ii) {
				if (m_mat[i][ii] != p_mat[i][ii])
					return false;
			}
		}
		return true;
	}
	 inline bool operator!=(Matrix& p_mat)
	{
		for (std::size_t i = 0; i < R; ++i) {
			for (std::size_t ii = 0; ii < C; ++ii) {
				if (m_mat[i][ii] != p_mat[i][ii])
					return true;
			}
		}
		return false;
	}
#pragma endregion	

};

MatrixTemplate std::ostream& operator<<(std::ostream& p_output, MatrixMacro& p_mat) {
	for (std::size_t i = 0; i < R; ++i) {
		p_output << '|';
		for (std::size_t ii = 0; ii < C; ++ii) {

			p_output << p_mat[i][ii];
			if (ii < C - 1)
				p_output << ' ';
		}
		p_output << '|' << std::endl;
	}
	return p_output;
}


#endif /* Matrix_h */
