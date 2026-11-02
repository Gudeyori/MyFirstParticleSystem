#pragma once
#include "raylib.h"

struct Particle
{
	// where is my particle?
	Vector2 center = Vector2{ 0, 0 };

	// every particle needs a radius
	float radius = 0;

	// what do they look like?
	Color color = BLACK;

	float speed = 0;
	float angle = 0;
	float gravity = 10;

	// recycling process
	bool active = false;

	void Activate(Vector2 center, float radius, Color color, float speed, float angle);

	void Draw();

	void Update();
};

// vector -> array or list
// vector2 -> a pair of float values or a point