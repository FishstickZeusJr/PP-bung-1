#pragma once

#include <exception>
#include <iostream>
#include <typeinfo>

template <typename T>
class Vector2d
{
private:
	T m_val1{};
	T m_val2{};

public:
	Vector2d(const T& val1 = 0, const T& val2 = 0)
		: m_val1{ val1 }
		, m_val2{ val2 }
	{}

	const T& operator[] (int index) const
	{
		if (index == 0)
			return m_val1;
		else if (index == 1)
			return m_val2;
		else
			throw std::exception{};
	}

	T& operator[] (int index)
	{
		return const_cast<T&>(std::as_const(*this)[index]);
	}

	friend std::ostream& operator<< (std::ostream& out, const Vector2d& vector) //prints vector
	{
		out << '[' << vector[0] << ", " << vector[1] << ']';
		return out;
	}

	//Operators work only with vectors and scalars of same type
	//Can implement additional templates to get around this, but too lazy
	friend Vector2d<T> operator+ (const Vector2d<T>& vector1, const Vector2d<T>& vector2) //elementwise addition
	{
		return Vector2d<T>{ vector1[0] + vector2[0], vector1[1] + vector2[1] };
	}

	friend Vector2d<T> operator- (const Vector2d<T>& vector1, const Vector2d<T>& vector2) //elementwise subtraction
	{
		return Vector2d<T>{ vector1[0] - vector2[0], vector1[1] - vector2[1] };
	}

	friend Vector2d<T> operator* (const Vector2d<T>& vector1, T multiplier) //scalar multiplication
	{
		return Vector2d<T>{ vector1[0] * multiplier, vector1[1] * multiplier };
	}

	friend Vector2d<T> operator/ (const Vector2d<T>& vector1, T divisor) //scalar division
	{
		return Vector2d<T>{ vector1[0] / divisor, vector1[1] / divisor };
	}

	friend bool operator== (const Vector2d<T>& vector1, const Vector2d<T>& vector2) //true if both elements equal
	{
		return (vector1[0] == vector2[0] && vector1[1] == vector2[1]);
	}
};