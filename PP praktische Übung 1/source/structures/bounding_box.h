#pragma once

#include <string>
#include "vector2d.h"

class BoundingBox
{
private:
	double x_min{};
	double x_max{};
	double y_min{};
	double y_max{};

public:
	BoundingBox(double x_min = 0, double x_max = 0, double y_min = 0, double y_max = 0); //Default constructor

	std::string get_string();
	double get_diagonal();
	void plotting_sanity_check();
	BoundingBox get_scaled(std::uint32_t scaling_factor);

	template <typename T>
	bool contains(const Vector2d<T>& vector) //Function doens't work when defined in .cpp file
	{
		if (vector[0] >= x_min && vector[0] <= x_max && vector[1] >= y_min && vector[1] <= y_max)
			return true;
		else
			return false;
	}

	BoundingBox get_quadrant(std::uint8_t quadrant);

};