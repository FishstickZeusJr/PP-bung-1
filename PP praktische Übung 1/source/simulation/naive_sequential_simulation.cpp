#include "simulation/naive_sequential_simulation.h"
#include "simulation/constants.h"
#include "physics/gravitation.h"
#include "physics/mechanics.h"

#include <cmath>
#include <omp.h>


void NaiveSequentialSimulation::calculate_forces(Universe& universe)
{
#pragma omp parallel for collapse(2)
	for (std::uint32_t i{ 0 }; i < universe.getNumBodies(); ++i)
	{
		double force{};

		for (std::uint32_t j{ 0 }; j < universe.getNumBodies(); ++j)
		{
			if (i != j)
				force += gravitational_force(universe.getMassAtIndex(i), universe.getMassAtIndex(j), universe.getDistance(universe.getPositionAtIndex(i), universe.getPositionAtIndex(j)));
		}

		universe.setForceAtIndex(force, i);
	}
}


void NaiveSequentialSimulation::calculate_velocities(Universe& universe)
{
#pragma omp parallel for
	for (std::uint32_t i{ 0 }; i < universe.getNumBodies(); ++i)
	{
		//Avoided creating intermediate variable for performance, but this might be too hard to read
		universe.setVelocityAtIndex(calculate_velocity(universe.getVelocityAtIndex(i), calculate_acceleration(universe.getForceAtIndex(i), universe.getMassAtIndex(i)), epoch_in_seconds), i);
	}
}