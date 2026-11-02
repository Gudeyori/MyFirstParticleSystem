#pragma once
#include <vector>
#include "Particle.h" // this is the file name

class ParticleSystem
{
public:

#define POOL_SIZE 1000 // max 1000 particles
	// object pooling -> todays topic!

	std::vector<Particle> pool; // particle here is a struct or class

	void Main(); // the Raylib stuff
	void Start(); // where starting stuff goes
	void Update(); // frame by frame calculation

private:
};