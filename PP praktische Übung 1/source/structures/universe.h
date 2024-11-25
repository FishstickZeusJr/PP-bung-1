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

	std::uint32_t getNumBodies() const { return numbodies; }
	std::uint32_t getCurrentEpoch() const { return current_simulation_epoch; }
	double getMassAtIndex(int index) const { return weights[index]; }
	Vector2d<double> getForceAtIndex(int index) const { return forces[index]; }
	Vector2d<double> getVelocityAtIndex(int index) const { return velocities[index]; }
	Vector2d<double> getPositionAtIndex(int index) const { return positions[index]; }
	double getDistance(Vector2d<double> pos1, Vector2d<double> pos2);

	void setMassAtIndex(double mass, int index) { weights[index] = mass; }
	void setForceAtIndex(Vector2d<double> force, int index) { forces[index] = force; }
	void setVelocityAtIndex(Vector2d<double> velocity, int index) { velocities[index] = velocity; }
	void setPositionAtIndex(Vector2d<double> position, int index) { positions[index] = position; }

};