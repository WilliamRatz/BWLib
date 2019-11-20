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

template<typename T, std::size_t R, std::size_t C>
class Matrix < T, R, C, MatrixMacro {
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
	inline Matrix& resize(std::size_t rows, std::size_t columns)
	{
		Vector<T, columns> temp[rows];

		for (std::size_t i = 0; i < (columns < C) ? columns : C; ++i)
		{
			for (std::size_t j = 0; j < (rows < R) ? rows : R; ++j)
			{
				temp[j][i] = m_mat[j][i];
			}
		}
		C = columns;
		R = rows;
		m_mat = temp;
	}

#pragma endregion

#pragma region arithmeticOperations
	inline void operator=(const Matrix& mat)
	{
		for (std::size_t i = 0; i < C; ++i) {
			for (std::size_t ii = 0; ii < R; ++ii) {
				m_mat[ii][i] = mat.m_mat[ii][i];
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
	inline Matrix operator+(const Matrix& mat) {

		Matrix temp(*this);
		return temp += mat;
	}
	inline Matrix operator-(const Matrix& mat) {

		Matrix temp(*this);
		return temp -= mat;
	}
	inline Matrix operator*(const Matrix& mat) {

		Matrix temp(*this);
		return temp *= mat;
	}

	inline Matrix& operator+=(const Matrix& mat)
	{
		for (std::size_t i = 0; i < R; ++i) {
			for (std::size_t ii = 0; ii < C; ++ii) {
				m_mat[i][ii] = m_mat[i][ii] + mat.m_mat[i][ii];
			}
		}
		return *this;
	}
	inline Matrix& operator-=(const Matrix& mat)
	{
		for (std::size_t i = 0; i < R; ++i) {
			for (std::size_t ii = 0; ii < C; ++ii) {
				m_mat[i][ii] = m_mat[i][ii] - mat.m_mat[i][ii];
			}
		}
		return *this;
	}
	inline Matrix& operator*=(const Matrix& mat)
	{
		T tempValue = (T)0;
		Matrix<T, R, R> tempMat;

		for (std::size_t i = 0; i < R; ++i) {
			for (std::size_t ii = 0; ii < R; ++ii) {
				for (std::size_t iii = 0; iii < C; ++iii) {
					tempValue += m_mat[i][iii] * mat.m_mat[iii][ii];
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
	inline bool operator==(Matrix& mat)
	{
		for (std::size_t i = 0; i < R; ++i) {
			for (std::size_t ii = 0; ii < C; ++ii) {
				if (m_mat[i][ii] != mat[i][ii])
					return false;
			}
		}
		return true;
	}
	inline bool operator!=(Matrix& mat)
	{
		for (std::size_t i = 0; i < R; ++i) {
			for (std::size_t ii = 0; ii < C; ++ii) {
				if (m_mat[i][ii] != mat[i][ii])
					return true;
			}
		}
		return false;
	}
#pragma endregion	

};

template<typename T>
class Matrix < T, 4, 4, MatrixMacro
{
private:
	Vector<T, 4> m_mat[4];

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

	Vector<T, 4>& operator[](const std::size_t index) {
		if (index >= 4) {
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

		for (long long i = 0; i < 4; ++i) {
			for (long long ii = 0; ii < 4; ++ii) {
				hash = (hash * 397) ^ static_cast<long long>(m_mat[i][ii]);
			}
		}

		return hash;
	}
	inline std::size_t countColumns()
	{
		return 4;
	}
	inline std::size_t countRows()
	{
		return 4;
	}

	inline Matrix& translate(float x, float y, float z)
	{
		if (4 != 4 || 4 != 4) {
			throw std::out_of_range("Your Matrix dont fit for 3D translation, check your dimensions");
		}

		Matrix trans3D;

		trans3D[0][3] = (T)x;
		trans3D[1][3] = (T)y;
		trans3D[2][3] = (T)z;

		*this *= trans3D;
		return *this;
	}
	inline Matrix& translate(Vector3 vec3)
	{
		if (4 != 4 || 4 != 4) {
			throw std::out_of_range("Your Matrix dont fit for 3D translation, check your dimensions");
		}

		Matrix trans3D;

		trans3D[0][3] = (T)vec3.x();
		trans3D[1][3] = (T)vec3.y();
		trans3D[2][3] = (T)vec3.z();

		*this *= trans3D;
		return *this;
	}
	inline Matrix& scale(float widthHeightDepth)
	{
		if (4 != 4 || 4 != 4) {
			throw std::out_of_range("Your Matrix dont fit for 3D scaleing, check your dimensions");
		}

		Matrix scal3D;

		scal3D[0][0] = (T)widthHeightDepth;
		scal3D[1][1] = (T)widthHeightDepth;
		scal3D[2][2] = (T)widthHeightDepth;

		*this *= scal3D;
		return *this;
	}
	inline Matrix& scale(float width, float height, float depth)
	{
		if (4 != 4 || 4 != 4) {
			throw std::out_of_range("Your Matrix dont fit for 3D scaleing, check your dimensions");
		}

		Matrix scal3D;

		scal3D[0][0] = (T)width;
		scal3D[1][1] = (T)height;
		scal3D[2][2] = (T)depth;

		*this *= scal3D;
		return *this;
	}
	inline Matrix& scale(Vector3 vec3)
	{
		if (4 != 4 || 4 != 4) {
			throw std::out_of_range("Your Matrix dont fit for 3D scaleing, check your dimensions");
		}

		Matrix scal3D;

		scal3D[0][0] = (T)vec3.x();
		scal3D[1][1] = (T)vec3.y();
		scal3D[2][2] = (T)vec3.z();

		*this *= scal3D;
		return *this;
	}
	inline Matrix& rotation3DAroundX(float angle)
	{
		if (4 != 4 || 4 != 4) {
			throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"X\", check your dimensions");
		}

		Matrix rotat3DX;
		double degress = (double)angle * BWMath::PI / 180; // change from Rad to degrees

		rotat3DX[1][1] = (T)std::cos(degress);
		rotat3DX[1][2] = (T)-std::sin(degress);
		rotat3DX[2][1] = (T)std::sin(degress);
		rotat3DX[2][2] = (T)std::cos(degress);

		this->operator*=(rotat3DX);
		return *this;
	}
	inline Matrix& rotation3DAroundY(float angle)
	{
		if (4 != 4 || 4 != 4) {
			throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"Y\", check your dimensions");
		}

		Matrix rotat3DY;
		double degress = (double)angle * BWMath::PI / 180; // change from Rad to degrees

		rotat3DY[0][0] = (T)std::cos(degress);
		rotat3DY[0][2] = (T)std::sin(degress);
		rotat3DY[2][0] = (T)-std::sin(degress);
		rotat3DY[2][2] = (T)std::cos(degress);

		this->operator*=(rotat3DY);
		return *this;
	}
	inline Matrix& rotation3DAroundZ(float angle)
	{
		if (4 != 4 || 4 != 4) {
			throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"Z\", check your dimensions");
		}

		Matrix rotat3DZ;
		double degress = (double)angle * BWMath::PI / 180; // change from Rad to degrees

		rotat3DZ[0][0] = (T)std::cos(degress);
		rotat3DZ[0][1] = (T)-std::sin(degress);
		rotat3DZ[1][0] = (T)std::sin(degress);
		rotat3DZ[1][1] = (T)std::cos(degress);

		this->operator*=(rotat3DZ);
		return *this;
	}

	inline Matrix& rotationAroundXlocal(float angle)
	{
		if (4 != 4 || 4 != 4) {
			throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"X\", check your dimensions");
		}
		Vector3 transformation(m_mat[0][3], m_mat[1][3], m_mat[2][3]);

		this->m_mat[0][3] = 0;
		this->m_mat[1][3] = 0;
		this->m_mat[2][3] = 0;

		this->rotation3DAroundX(angle);

		this->m_mat[0][3] = transformation.x();
		this->m_mat[1][3] = transformation.y();
		this->m_mat[2][3] = transformation.z();

		return *this;
	}
	inline Matrix& rotationAroundYlocal(float angle)
	{
		if (4 != 4 || 4 != 4) {
			throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"Y\", check your dimensions");
		}

		Vector3 transformation(m_mat[0][3], m_mat[1][3], m_mat[2][3]);

		this->m_mat[0][3] = 0;
		this->m_mat[1][3] = 0;
		this->m_mat[2][3] = 0;

		this->rotation3DAroundY(angle);

		this->m_mat[0][3] = transformation.x();
		this->m_mat[1][3] = transformation.y();
		this->m_mat[2][3] = transformation.z();

		return *this;
	}
	inline Matrix& rotationAroundZlocal(float angle)
	{
		if (4 != 4 || 4 != 4) {
			throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"Z\", check your dimensions");
		}

		Vector3 transformation(m_mat[0][3], m_mat[1][3], m_mat[2][3]);

		this->m_mat[0][3] = 0;
		this->m_mat[1][3] = 0;
		this->m_mat[2][3] = 0;

		this->rotation3DAroundZ(angle);

		this->m_mat[0][3] = transformation.x();
		this->m_mat[1][3] = transformation.y();
		this->m_mat[2][3] = transformation.z();

		return *this;

	}

	inline Matrix& rotationAroundArbitararyAxis(float angle, Vector3 axis)
	{
		if (4 != 4 || 4 != 4) {
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

	inline Matrix& perspectivProjection(float windowWidth, float windowHeight, float nearPlane, float farPlane)
	{
		if (4 != 4 || 4 != 4) {
			throw std::out_of_range("Your Matrix dont fit for perspectiv projection, check your dimensions");
		}

		Matrix perProj;

		perProj[0][0] = (T)((2 * nearPlane) / windowWidth);
		perProj[1][1] = (T)((2 * nearPlane) / windowHeight);
		perProj[2][2] = (T)(farPlane / (farPlane - nearPlane));
		perProj[2][3] = (T)1;
		perProj[3][2] = (T)((-farPlane * nearPlane) / (farPlane - nearPlane));
		perProj[3][3] = 0;
		*this = perProj;
		return *this;
	}
	inline Matrix& orthogonalProjection(float windowWidth, float windowHeight, float nearPlane, float farPlane)
	{
		if (4 != 4 || 4 != 4) {
			throw std::out_of_range("Your Matrix dont fit for orthogonal projection, check your dimensions");
		}

		Matrix perProj;

		perProj[0][0] = (T)(2 / windowWidth);
		perProj[1][1] = (T)(2 / windowHeight);
		perProj[2][2] = (T)(1 / (farPlane - nearPlane));
		perProj[3][3] = (T)(-nearPlane / (farPlane - nearPlane));

		if (4 > 3)
		{
			perProj[3][3] = (T)1;
		}

		*this = perProj;
		return *this;
	}

	inline Vector3 getScale()
	{
		if (4 != 4 || 4 != 4)
		{
			throw std::out_of_range("Your Matrix dont fit for 3D actions \"Z\", check your dimensions");
		}
			return Vector3(m_mat[0][0], m_mat[1][1], m_mat[2][2]);

	}
	inline Vector3 getTransform()
	{
		if (4 != 4 || 4 != 4)
		{
			throw std::out_of_range("Your Matrix dont fit for 3D actions \"Z\", check your dimensions");
		}
		return Vector3(m_mat[0][3], m_mat[1][3], m_mat[2][3]);
	}
	inline Vector3 getEulerAngles()
	{
		if (4 != 4 || 4 != 4)
		{
			throw std::out_of_range("Your Matrix dont fit for 3D actions \"Z\", check your dimensions");
		}

			float sy = sqrt(m_mat[0][0] * m_mat[0][0] + m_mat[1][0] * m_mat[1][0]);

			bool singular = sy < 1e-6; // If

			Vector3 temp;
			if (!singular)
			{
				temp.x(std::atan2(m_mat[2][1], m_mat[2][2]));
				temp.y(std::atan2(-m_mat[2][0], sy));
				temp.z(std::atan2(m_mat[1][0], m_mat[0][0]));
			}
			else
			{
				temp.x(std::atan2(-m_mat[1][2], m_mat[1][1]));
				temp.y(std::atan2(-m_mat[2][0], sy));
				temp.z(0);
			}
			return temp;

	}

	inline Matrix& zero() {

		for (std::size_t i = 0; i < 4; ++i) {
			for (std::size_t ii = 0; ii < 4; ++ii) {
				m_mat[ii][i] = T(0);
			}
		}
		return *this;

	}
	inline Matrix& identity() {

		for (std::size_t i = 0; i < 4; ++i) {
			for (std::size_t ii = 0; ii < 4; ++ii) {
				m_mat[ii][i] = (i == ii) ? T(1) : T(0);
			}
		}
		return *this;

	}
	inline Matrix& inverse()
	{
		Matrix<T, 4, 4 * 2> tempMat;
		float temp;


		for (std::size_t i = 0; i < 4; ++i) {
			for (std::size_t ii = 0; ii < 4; ++ii) {
				tempMat[ii][i] = m_mat[ii][i];
			}
		}


		for (int i = 0; i < 4; i++) {

			for (int j = 0; j < 2 * 4; j++) {
				if (j == (i + 4))
					tempMat[i][j] = 1;
			}
		}

		for (int i = 4 - 1; i > 0; i--) {

			if (tempMat[i - 1][0] < tempMat[i][0])
				for (int j = 0; j < 2 * 4; j++) {
					temp = tempMat[i][j];
					tempMat[i][j] = tempMat[i - 1][j];
					tempMat[i - 1][j] = temp;
				}
		}

		for (int i = 0; i < 4; i++) {

			for (int j = 0; j < 4; j++) {

				if (j != i) {

					temp = tempMat[j][i] / tempMat[i][i];
					for (int k = 0; k < 2 * 4; k++) {
						tempMat[j][k] -= tempMat[i][k] * temp;
					}
				}
			}
		}

		for (int i = 0; i < 4; i++) {

			temp = tempMat[i][i];
			for (int j = 0; j < 2 * 4; j++) {

				tempMat[i][j] = tempMat[i][j] / temp;
			}
		}


		for (std::size_t i = 4; i < 4 * 2; ++i) {
			for (std::size_t ii = 0; ii < 4; ++ii) {
				m_mat[ii][i - 4] = tempMat[ii][i];
			}
		}

		std::cout << *this << std::endl;

		return *this;
	}
	inline Matrix<T, 4, 4> transpose()
	{
		Matrix<T, 4, 4> temp;

		for (std::size_t i = 0; i < 4; ++i) {
			for (std::size_t ii = 0; ii < 4; ++ii) {
				temp[i][ii] = m_mat[ii][i];
			}
		}

		return temp;
	}
	inline Matrix& resize(std::size_t rows, std::size_t columns)
	{
		Vector<T, columns> temp[rows];

		for (std::size_t i = 0; i < (columns < 4) ? columns : 4; ++i)
		{
			for (std::size_t j = 0; j < (rows < 4) ? rows : 4; ++j)
			{
				temp[j][i] = m_mat[j][i];
			}
		}
		4 = columns;
		4 = rows;
		m_mat = temp;
	}

#pragma endregion

#pragma region arithmeticOperations
	inline void operator=(const Matrix& mat)
	{
		for (std::size_t i = 0; i < 4; ++i) {
			for (std::size_t ii = 0; ii < 4; ++ii) {
				m_mat[ii][i] = mat.m_mat[ii][i];
			}
		}
	}
	inline Matrix operator-()
	{
		for (std::size_t i = 0; i < 4; ++i) {
			for (std::size_t ii = 0; ii < 4; ++ii) {
				m_mat[ii][i] = -m_mat[ii][i];
			}
		}

		return *this;
	}
	inline Matrix operator+(const Matrix& mat) {

		Matrix temp(*this);
		return temp += mat;
	}
	inline Matrix operator-(const Matrix& mat) {

		Matrix temp(*this);
		return temp -= mat;
	}
	inline Matrix operator*(const Matrix& mat) {

		Matrix temp(*this);
		return temp *= mat;
	}

	inline Matrix& operator+=(const Matrix& mat)
	{
		for (std::size_t i = 0; i < 4; ++i) {
			for (std::size_t ii = 0; ii < 4; ++ii) {
				m_mat[i][ii] = m_mat[i][ii] + mat.m_mat[i][ii];
			}
		}
		return *this;
	}
	inline Matrix& operator-=(const Matrix& mat)
	{
		for (std::size_t i = 0; i < 4; ++i) {
			for (std::size_t ii = 0; ii < 4; ++ii) {
				m_mat[i][ii] = m_mat[i][ii] - mat.m_mat[i][ii];
			}
		}
		return *this;
	}
	inline Matrix& operator*=(const Matrix& mat)
	{
		T tempValue = (T)0;
		Matrix<T, 4, 4> tempMat;

		for (std::size_t i = 0; i < 4; ++i) {
			for (std::size_t ii = 0; ii < 4; ++ii) {
				for (std::size_t iii = 0; iii < 4; ++iii) {
					tempValue += m_mat[i][iii] * mat.m_mat[iii][ii];
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
	inline bool operator==(Matrix& mat)
	{
		for (std::size_t i = 0; i < 4; ++i) {
			for (std::size_t ii = 0; ii < 4; ++ii) {
				if (m_mat[i][ii] != mat[i][ii])
					return false;
			}
		}
		return true;
	}
	inline bool operator!=(Matrix& mat)
	{
		for (std::size_t i = 0; i < 4; ++i) {
			for (std::size_t ii = 0; ii < 4; ++ii) {
				if (m_mat[i][ii] != mat[i][ii])
					return true;
			}
		}
		return false;
	}
#pragma endregion	

};

template<typename T>
class Matrix < T, 3, 3, MatrixMacro
{
	private:
	Vector<T, 3> m_mat[3];

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

	Vector<T, 3>& operator[](const std::size_t index) {
		if (index >= 3) {
			throw std::out_of_range("Index out of Range");
		}
		return m_mat[index];
	}

#pragma region methods
	
	inline Vector2 Left()
	{
		return Vector2(-m_mat[0][0], -m_mat[1][0]);
	}
	inline Vector2 Right()
	{
		return Vector2(m_mat[0][0], m_mat[1][0]);
	}
	inline Vector2 Up()
	{
		return Vector2(m_mat[0][1], m_mat[1][1]);
	}
	inline Vector2 Down()
	{
		return Vector2(-m_mat[0][1], -m_mat[1][1]);
	}

	/*inline double Yaw()
	{
		return (m_mat[0][0] == (T)1 || m_mat[0][0] == (T)-1) ? std::atan2f(m_mat[0][2], m_mat[2][3]) : std::atan2f(-m_mat[2][0], m_mat[0][0]);
	}
	inline double Roll()
	{
		return (m_mat[0][0] == (T)1 || m_mat[0][0] == (T)-1) ? 0 : std::atan2(-m_mat[1][2], m_mat[1][1]);
	}*/

	inline std::size_t getHashCode()
	{
		long long hash = m_mat[0][0];

		for (long long i = 0; i < 3; ++i) {
			for (long long ii = 0; ii < 3; ++ii) {
				hash = (hash * 397) ^ static_cast<long long>(m_mat[i][ii]);
			}
		}

		return hash;
	}
	inline std::size_t countColumns()
	{
		return 3;
	}
	inline std::size_t countRows()
	{
		return 3;
	}

	inline Matrix& translate(float x, float y)
	{
		if (3 < 3 || 3 < 2) {
			throw std::out_of_range("Your Matrix don't fit for 2D translation check your dimensions");
		}

		 Matrix trans2D;

		trans2D[0][2] = (T)x;
		trans2D[1][2] = (T)y;

		*this *= trans2D;

		return *this;
	}
	inline Matrix& scale(float widthHeight)
	{
		if (3 != 3 || 3 != 3) {
			throw std::out_of_range("Your Matrix dont fit for 2D scaleing, check your dimensions");
		}

		Matrix scal2D;

		scal2D[0][2] = (T)widthHeight;
		scal2D[1][2] = (T)widthHeight;

		*this *= scal2D;

		return *this;
	}
	inline Matrix& scale(float width, float height)
	{
		if (3 != 3 || 3 != 3) {
			throw std::out_of_range("Your Matrix dont fit for 2D scaleing, check your dimensions");
		}

		Matrix scal2D;

		scal2D[0][2] = (T)width;
		scal2D[1][2] = (T)height;

		*this *= scal2D;

		return *this;
	}
	inline Matrix& scale(Vector2 vec2)
	{
		if (3 != 3 || 3 != 3) {
			throw std::out_of_range("Your Matrix dont fit for 2D scaleing, check your dimensions");
		}

		Matrix scal2D;

		scal2D[0][2] = (T)vec2.x();
		scal2D[1][2] = (T)vec2.y();

		*this *= scal2D;

		return *this;
	}
	inline Matrix& rotation(float angle)
	{
		if (3 != 3 || 3 != 3) {
			throw std::out_of_range("Your Matrix dont fit for 2D rotation, check your dimensions");
		}

		Matrix rotat2D;
		double degress = (double)angle * BWMath::PI / 180; // change from Rad to degrees

		rotat2D[0][0] = (T)std::cos(degress);
		rotat2D[0][1] = (T)std::sin(degress);
		rotat2D[1][0] = (T)-std::sin(degress);
		rotat2D[1][1] = (T)std::cos(degress);

		*this *= rotat2D;
		return *this;
	}

	inline Vector2 getScale()
	{
		if (3 != 3 || 3 != 3)
		{
			throw std::out_of_range("Your Matrix dont fit for 2D actions \"Z\", check your dimensions");
		}
			return Vector2(m_mat[0][0], m_mat[1][1]);

	}
	inline Vector2 getTransform()
	{
		if (3 != 3 || 3 != 3)
		{
			throw std::out_of_range("Your Matrix dont fit for 2D actions \"Z\", check your dimensions");
		}
			return Vector2(m_mat[0][3], m_mat[1][3]);

	}
	inline Vector2 getEulerAngles()
	{
		if (3 != 3 || 3 != 3)
		{
			throw std::out_of_range("Your Matrix dont fit for 2D actions \"Z\", check your dimensions");
		}
			float sy = sqrt(m_mat[0][0] * m_mat[0][0] + m_mat[1][0] * m_mat[1][0]);

			bool singular = sy < 1e-6; // If

			Vector2 temp;
			if (!singular)
			{
				temp.x(std::atan2(m_mat[2][1], m_mat[2][2]));
				temp.y(std::atan2(-m_mat[2][0], sy));
			}
			else
			{
				temp.x(std::atan2(-m_mat[1][2], m_mat[1][1]));
				temp.y(std::atan2(-m_mat[2][0], sy));
			}
			return temp;

	}

	inline Matrix& zero() {

		for (std::size_t i = 0; i < 3; ++i) {
			for (std::size_t ii = 0; ii < 3; ++ii) {
				m_mat[ii][i] = T(0);
			}
		}
		return *this;

	}
	inline Matrix& identity() {

		for (std::size_t i = 0; i < 3; ++i) {
			for (std::size_t ii = 0; ii < 3; ++ii) {
				m_mat[ii][i] = (i == ii) ? T(1) : T(0);
			}
		}
		return *this;

	}
	inline Matrix& inverse()
	{
		Matrix<T, 3, 3 * 2> tempMat;
		float temp;


		for (std::size_t i = 0; i < 3; ++i) {
			for (std::size_t ii = 0; ii < 3; ++ii) {
				tempMat[ii][i] = m_mat[ii][i];
			}
		}


		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 2 * 3; j++) {
				if (j == (i + 3))
					tempMat[i][j] = 1;
			}
		}

		for (int i = 3 - 1; i > 0; i--) {

			if (tempMat[i - 1][0] < tempMat[i][0])
				for (int j = 0; j < 2 * 3; j++) {
					temp = tempMat[i][j];
					tempMat[i][j] = tempMat[i - 1][j];
					tempMat[i - 1][j] = temp;
				}
		}

		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 3; j++) {

				if (j != i) {

					temp = tempMat[j][i] / tempMat[i][i];
					for (int k = 0; k < 2 * 3; k++) {
						tempMat[j][k] -= tempMat[i][k] * temp;
					}
				}
			}
		}

		for (int i = 0; i < 3; i++) {

			temp = tempMat[i][i];
			for (int j = 0; j < 2 * 3; j++) {

				tempMat[i][j] = tempMat[i][j] / temp;
			}
		}


		for (std::size_t i = 3; i < 3 * 2; ++i) {
			for (std::size_t ii = 0; ii < 3; ++ii) {
				m_mat[ii][i - 3] = tempMat[ii][i];
			}
		}

		std::cout << *this << std::endl;

		return *this;
	}
	inline Matrix<T, 3, 3> transpose()
	{
		Matrix<T, 3, 3> temp;

		for (std::size_t i = 0; i < 3; ++i) {
			for (std::size_t ii = 0; ii < 3; ++ii) {
				temp[i][ii] = m_mat[ii][i];
			}
		}

		return temp;
	}
	inline Matrix& resize(std::size_t rows, std::size_t columns)
	{
		Vector<T, columns> temp[rows];

		for (std::size_t i = 0; i < (columns < 3) ? columns : 3; ++i)
		{
			for (std::size_t j = 0; j < (rows < 3) ? rows : 3; ++j)
			{
				temp[j][i] = m_mat[j][i];
			}
		}
		3 = columns;
		3 = rows;
		m_mat = temp;
	}

#pragma endregion

#pragma region arithmeticOperations
	inline void operator=(const Matrix& mat)
	{
		for (std::size_t i = 0; i < 3; ++i) {
			for (std::size_t ii = 0; ii < 3; ++ii) {
				m_mat[ii][i] = mat.m_mat[ii][i];
			}
		}
	}
	inline Matrix operator-()
	{
		for (std::size_t i = 0; i < 3; ++i) {
			for (std::size_t ii = 0; ii < 3; ++ii) {
				m_mat[ii][i] = -m_mat[ii][i];
			}
		}

		return *this;
	}
	inline Matrix operator+(const Matrix& mat) {

		Matrix temp(*this);
		return temp += mat;
	}
	inline Matrix operator-(const Matrix& mat) {

		Matrix temp(*this);
		return temp -= mat;
	}
	inline Matrix operator*(const Matrix& mat) {

		Matrix temp(*this);
		return temp *= mat;
	}

	inline Matrix& operator+=(const Matrix& mat)
	{
		for (std::size_t i = 0; i < 3; ++i) {
			for (std::size_t ii = 0; ii < 3; ++ii) {
				m_mat[i][ii] = m_mat[i][ii] + mat.m_mat[i][ii];
			}
		}
		return *this;
	}
	inline Matrix& operator-=(const Matrix& mat)
	{
		for (std::size_t i = 0; i < 3; ++i) {
			for (std::size_t ii = 0; ii < 3; ++ii) {
				m_mat[i][ii] = m_mat[i][ii] - mat.m_mat[i][ii];
			}
		}
		return *this;
	}
	inline Matrix& operator*=(const Matrix& mat)
	{
		T tempValue = (T)0;
		Matrix<T, 3, 3> tempMat;

		for (std::size_t i = 0; i < 3; ++i) {
			for (std::size_t ii = 0; ii < 3; ++ii) {
				for (std::size_t iii = 0; iii < 3; ++iii) {
					tempValue += m_mat[i][iii] * mat.m_mat[iii][ii];
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
	inline bool operator==(Matrix& mat)
	{
		for (std::size_t i = 0; i < 3; ++i) {
			for (std::size_t ii = 0; ii < 3; ++ii) {
				if (m_mat[i][ii] != mat[i][ii])
					return false;
			}
		}
		return true;
	}
	inline bool operator!=(Matrix& mat)
	{
		for (std::size_t i = 0; i < 3; ++i) {
			for (std::size_t ii = 0; ii < 3; ++ii) {
				if (m_mat[i][ii] != mat[i][ii])
					return true;
			}
		}
		return false;
	}
#pragma endregion	

};

MatrixTemplate std::ostream& operator<<(std::ostream& output, Matrix < T, R, C,MatrixMacro& mat) {
	for (std::size_t i = 0; i < R; ++i) {
		output << '|';
		for (std::size_t ii = 0; ii < C; ++ii) {

			output << mat[i][ii];
			if (ii < C - 1)
				output << ' ';
		}
		output << '|' << std::endl;
	}
	return output;
}


#endif /* Matrix_h */
