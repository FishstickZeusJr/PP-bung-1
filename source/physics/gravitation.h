#pragma once

#include <stdexcept>
#include <cmath>

inline constexpr double gravitational_constant{ 6.67430e-11 };

static double gravitational_force(double m_1, double m_2, double d)
{
	if (d == 0)
		throw std::invalid_argument("Die Distanz d darf nicht null sein.");

	return gravitational_constant * m_1 * m_2 / (d * d);
}