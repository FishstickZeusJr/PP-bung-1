#pragma once

#include <vector>
#include "vector2d.h"
#include "bounding_box.h"

class Universe
{
private:
	std::uint32_t					numbodies{};
	std::uint32_t					current_simulation_epoch{};
	std::vector<double>				weights{};						//in kg
	std::vector<Vector2d<double>>	forces{};						//in N
	std::vector<Vector2d<double>>	velocities{};					// in m/s
	std::vector<Vector2d<double>>	positions{};					// in m

public:
	Universe(std::uint32_t numbodies = 0, std::uint32_t current_simulation_epoch = 0); //Default constructor

	BoundingBox get_bounding_box();

};