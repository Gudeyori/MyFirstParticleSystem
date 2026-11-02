#include "Particle.h"
#include "raymath.h"


void Particle::Activate(Vector2 center, float radius, Color color, float speed, float angle)
{
	this->center = center;
	this->radius = radius;
	this->color = color;
	this->speed = speed;
	this->angle = angle;
	this->active = true;
}

void Particle::Draw()
{
	if (this->active)
		DrawCircleV(center, radius, color);
}

void Particle::Update() // make it older, darker, larger, as the time passes
{


	if (!this->active) return;

	center.y += sin(angle * DEG2RAD) * speed + gravity;
	center.x += cos(angle * DEG2RAD) * speed;

	radius += 1.0f;

	float alpha = color.a;

	alpha -= 10;
	color.a = alpha;

	if (alpha < 0) // if the object is no longer visible
		active = false;
}