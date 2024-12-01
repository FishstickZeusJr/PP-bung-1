#pragma once

template <typename T>
static Vector2d<T> calculate_acceleration(Vector2d<T> force, T mass)
{
	if (mass == 0)
		throw std::invalid_argument("Die Masse darf nicht null sein.");

	return Vector2d<T>{ force[0] / mass, force[1] / mass };
}

template <typename T>
static Vector2d<T> calculate_velocity(Vector2d<T> v_0, Vector2d<T> acceleration, T time)
{
	return Vector2d<T>{ v_0[0] + acceleration[0] * time, v_0[1] + acceleration[1] * time };
}