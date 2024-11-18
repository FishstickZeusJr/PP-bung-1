#include "universe.h"

Universe::Universe(std::uint32_t numbodies, std::uint32_t current_simulation_epoch)
	: numbodies{ numbodies }
	, current_simulation_epoch{ current_simulation_epoch }
	, weights{ std::vector<double>(numbodies) }
	, forces{ std::vector<Vector2d<double>>(numbodies) }
	, velocities{ std::vector<Vector2d<double>>(numbodies) }
	, positions{ std::vector<Vector2d<double>>(numbodies) }
{}


BoundingBox Universe::get_bounding_box()
{
	double x_min{ positions[0][0] };
	double x_max{ positions[0][0] };
	double y_min{ positions[0][1] };
	double y_max{ positions[0][1] };

	
	for (std::uint32_t i{ 1 }; i < numbodies; ++i) //Can probably be implemented better with std::max_element
	{
		if (positions[i][0] < x_min)
			x_min = positions[i][0];
		else if (positions[i][0] > x_max)
			x_max = positions[i][0];

		if (positions[i][1] < y_min)
			y_min = positions[i][1];
		else if (positions[i][1] > y_max)
			y_max = positions[i][1];
	}

	return BoundingBox{ x_min, x_max, y_min, y_max };
}
