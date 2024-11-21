#pragma once

template <typename T>
static Vector2d<T> calculate_acceleration(Vector2d<T> force, double mass)
{
	return Vector2d<T>{ force[0] / mass, force[1] / mass };
}

template <typename T>
static Vector2d<T> calculate_velocity(Vector2d<T> v_0, Vector2d<T> acceleration, double time)
{
	return Vector2d<T>{ v_0[0] + acceleration[0] * time, v_0[1] + acceleration[1] * time };
}