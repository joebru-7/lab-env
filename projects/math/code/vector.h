#pragma once
class Vector
{
	float data[4];
public:
	constexpr Vector() :data{0,0,0,1} {};
	constexpr Vector(float x, float y, float z, float w = 1) : data{ x,y,z,w } {};

	constexpr Vector operator+(const Vector& other) const
	{
		return Vector(data[0] + other[0], data[1] + other[1], data[2] + other[2]);
	}
	constexpr Vector operator-(const Vector& other) const
	{
		return Vector(data[0] - other[0], data[1] - other[1], data[2] - other[2]);
	}
	constexpr Vector operator-() const
	{
		return Vector(-data[0], -data[1], -data[2]);
	}
	constexpr float operator[](int i) const
	{
		return data[i];
	}

	constexpr float& operator[](int i)
	{
		return data[i];
	};

	constexpr bool operator==(const Vector& other) const
	{
		return data[0] == other[0] &&
			data[1] == other[1] &&
			data[2] == other[2] &&
			data[3] == other[3];
	}

	constexpr bool operator!= (const Vector& other) const
	{
		return *this != other;
	}

	constexpr Vector operator*(const float f) const
	{
		return Vector(data[0] * f, data[1] * f, data[2] * f);
	}

	constexpr float dot(const Vector& other)const
	{
		return data[0] * other[0] +
			data[1] * other[1] +
			data[2] * other[2];
	}
	static constexpr float dot(const Vector& v1, const Vector& v2)
	{
		return v1.dot(v2);
	}
	constexpr Vector cross(const Vector& other)const 
	{
		return Vector(
			(data[1] * other[2]) - (data[2] * other[1]),
			(data[2] * other[0]) - (data[0] * other[2]),
			(data[0] * other[1]) - (data[1] * other[0])
		);

	}
	static constexpr Vector cross(const Vector& v1, const Vector& v2)
	{
		return v1.cross(v2);
	}

	float length() const 
	{
		// l = sqrt(x^2 + y^2 + z^2)
			return pow(0.5f,data[0] * data[0] + data[1] * data[1] + data[2] * data[2]);
	}
	inline Vector norm() const;
};

inline Vector operator*(const float& left, const Vector& right)
{
	return right * left;
}

inline Vector Vector::norm() const
{
	return 1.f / length() * (*this);
}