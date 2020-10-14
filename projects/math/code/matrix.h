#pragma once
#include "vector.h"
class Matrix
{
	float data[16];
	/*
	[0 ,1 ,2 ,3,
	 4 ,5 ,6 ,7,
	 8 ,9 ,10,11,
	 12,13,14,15]
	*/
public:
	constexpr Matrix() :
		data
	{ 1,0,0,0,
	 0,1,0,0,
	 0,0,1,0,
	 0,0,0,1 } {};

	constexpr Matrix(
		const float a, const float b, const float c, const float d,
		const float e, const float f, const float g, const float h,
		const float i, const float j, const float k, const float l,
		const float m, const float n, const float o, const float p)
		:data{ a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p }
	{};

	constexpr Matrix(const Vector& v):
		data{ 1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 }
	{
		data[3] = v[0];
		data[7] = v[1];
		data[11] = v[2];
	}

	constexpr Matrix(float a[16])
		:data{0}
	{
		for (size_t i = 0; i < 16; i++)
		{
			data[i] = a[i];
		}
	}

	static constexpr Matrix getTranslation(const Vector& v)
	{
		return Matrix(v);
	}

	constexpr float* operator[](int index)
	{
		return &data[index * 4];
	}
	constexpr const float* operator[](int index) const
	{
		return &data[index * 4];
	}
	constexpr float Get(const int& x, const int& y) const
	{
		return data[x + y * 4];
	}
	constexpr float Get(const int& i) const
	{
		return data[i];
	}


	static constexpr Matrix getScaleMatrix(Vector scale)
	{
		Matrix m = Matrix();
		m[0][0] = scale[0];
		m[1][1] = scale[1];
		m[2][2] = scale[2];
		m[3][3] = scale[3];
		return m;
	}

	[[nodiscard]]
	float* getArray() const
	{
		float f[16] = {};
		for (int i = 0; i < 16; i++)
		{
			f[i] = data[i];
		}
		return f;
	}


	Matrix operator*(const Matrix& that) const
	{
		float* f = new float[16];
		// x, y positoner i nya arrayen 
		// i	
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				f[x + y * 4] = 0;
				for (int i = 0; i < 4; i++)
				{
					f[x + y * 4] += this->Get(x, i) * that.Get(i, y);
				}
			}
		}
		Matrix ret = Matrix(f);
		return ret;

	}

	constexpr Vector operator*(const Vector& that) const
	{
		float f[4] = {};
		for (int x = 0; x < 4; x++)
		{
			f[x] = 0;
			for (int y = 0; y < 4; y++)
			{
				f[x] += this->Get(y, x) * that[y];
			}
		}
		return Vector(f[0], f[1], f[2], f[3]);
	}

	bool operator==(const Matrix& that) const
	{
		for (int i = 0; i < 16; i++)
		{
			if (this->Get(i) != that.Get(i))
			{
				return false;
			}
		}
		return true;
	}

	static Matrix getRotMatrixX(const float rad)
	{
		float c = cosf(rad);
		float s = sinf(rad);

		return
			Matrix(
				1, 0, 0, 0,
				0, c,-s, 0,
				0, s, c, 0,
				0, 0, 0, 1
				);


	}
	static Matrix getRotMatrixY(const float rad)
	{
		float c = cosf(rad);
		float s = sinf(rad);


		return
			Matrix(
				c, 0, 0, s,
				0, 1, 0, 0,
				0, s, 1, 0,
			   -s, 0, 0, c
				);
	}
	static Matrix getRotMatrixZ(const float rad)
	{
		float c = cosf(rad);
		float s = sinf(rad);

		return
			Matrix(
				c,-s, 0, 0,
				s, c, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
			);
	}
	static Matrix getRotMatrix(const float rad, const Vector& v)
	{
		const float& c = cosf(rad);
		const float& s = sinf(rad);

		Vector temp = v.norm();
		const float x = temp[0];
		const float y = temp[1];
		const float z = temp[2];

		return Matrix(
			
				c + x * x * (1 - c),			x * y * (1 - c) - z * s,	x * z * (1 - c) + y * s,	0,
					y * x * (1 - c) + z * s,	c + y * y * (1 - c),		y * z * (1 - c) - x * s,	0,
					z * x * (1 - c) - y * s,	z * y * (1 - c) + x * s,	c + z * z * (1 - c),		0,
					0,							0,							0,							1

			);
	}


	[[nodiscard]]
	static Matrix GetInverse(Matrix matrix)
	{
		auto m = matrix.getArray();
		float inv[16], det;
		float* invOut = new float[16];

		inv[0] = m[5] * m[10] * m[15] -
			m[5] * m[11] * m[14] -
			m[9] * m[6] * m[15] +
			m[9] * m[7] * m[14] +
			m[13] * m[6] * m[11] -
			m[13] * m[7] * m[10];

		inv[4] = -m[4] * m[10] * m[15] +
			m[4] * m[11] * m[14] +
			m[8] * m[6] * m[15] -
			m[8] * m[7] * m[14] -
			m[12] * m[6] * m[11] +
			m[12] * m[7] * m[10];

		inv[8] = m[4] * m[9] * m[15] -
			m[4] * m[11] * m[13] -
			m[8] * m[5] * m[15] +
			m[8] * m[7] * m[13] +
			m[12] * m[5] * m[11] -
			m[12] * m[7] * m[9];

		inv[12] = -m[4] * m[9] * m[14] +
			m[4] * m[10] * m[13] +
			m[8] * m[5] * m[14] -
			m[8] * m[6] * m[13] -
			m[12] * m[5] * m[10] +
			m[12] * m[6] * m[9];

		inv[1] = -m[1] * m[10] * m[15] +
			m[1] * m[11] * m[14] +
			m[9] * m[2] * m[15] -
			m[9] * m[3] * m[14] -
			m[13] * m[2] * m[11] +
			m[13] * m[3] * m[10];

		inv[5] = m[0] * m[10] * m[15] -
			m[0] * m[11] * m[14] -
			m[8] * m[2] * m[15] +
			m[8] * m[3] * m[14] +
			m[12] * m[2] * m[11] -
			m[12] * m[3] * m[10];

		inv[9] = -m[0] * m[9] * m[15] +
			m[0] * m[11] * m[13] +
			m[8] * m[1] * m[15] -
			m[8] * m[3] * m[13] -
			m[12] * m[1] * m[11] +
			m[12] * m[3] * m[9];

		inv[13] = m[0] * m[9] * m[14] -
			m[0] * m[10] * m[13] -
			m[8] * m[1] * m[14] +
			m[8] * m[2] * m[13] +
			m[12] * m[1] * m[10] -
			m[12] * m[2] * m[9];

		inv[2] = m[1] * m[6] * m[15] -
			m[1] * m[7] * m[14] -
			m[5] * m[2] * m[15] +
			m[5] * m[3] * m[14] +
			m[13] * m[2] * m[7] -
			m[13] * m[3] * m[6];

		inv[6] = -m[0] * m[6] * m[15] +
			m[0] * m[7] * m[14] +
			m[4] * m[2] * m[15] -
			m[4] * m[3] * m[14] -
			m[12] * m[2] * m[7] +
			m[12] * m[3] * m[6];

		inv[10] = m[0] * m[5] * m[15] -
			m[0] * m[7] * m[13] -
			m[4] * m[1] * m[15] +
			m[4] * m[3] * m[13] +
			m[12] * m[1] * m[7] -
			m[12] * m[3] * m[5];

		inv[14] = -m[0] * m[5] * m[14] +
			m[0] * m[6] * m[13] +
			m[4] * m[1] * m[14] -
			m[4] * m[2] * m[13] -
			m[12] * m[1] * m[6] +
			m[12] * m[2] * m[5];

		inv[3] = -m[1] * m[6] * m[11] +
			m[1] * m[7] * m[10] +
			m[5] * m[2] * m[11] -
			m[5] * m[3] * m[10] -
			m[9] * m[2] * m[7] +
			m[9] * m[3] * m[6];

		inv[7] = m[0] * m[6] * m[11] -
			m[0] * m[7] * m[10] -
			m[4] * m[2] * m[11] +
			m[4] * m[3] * m[10] +
			m[8] * m[2] * m[7] -
			m[8] * m[3] * m[6];

		inv[11] = -m[0] * m[5] * m[11] +
			m[0] * m[7] * m[9] +
			m[4] * m[1] * m[11] -
			m[4] * m[3] * m[9] -
			m[8] * m[1] * m[7] +
			m[8] * m[3] * m[5];

		inv[15] = m[0] * m[5] * m[10] -
			m[0] * m[6] * m[9] -
			m[4] * m[1] * m[10] +
			m[4] * m[2] * m[9] +
			m[8] * m[1] * m[6] -
			m[8] * m[2] * m[5];

		det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

		if (det == 0)
		{
		}

		det = 1.0f / det;

		for (int i = 0; i < 16; i++)
		{
			invOut[i] = inv[i] * det;
		}
		return Matrix(invOut);
	}


};

