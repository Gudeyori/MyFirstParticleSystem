#pragma once
#include <raylib.h>
#include <vector>
#include "MemoryTile.h"

class Memory
{
public:

#define GAP 12 // whatever number i want
#define WAIT_TIME 0.5

	std::vector<MemoryTile> tiles;

	int gridSize = 3;
	int widthHeight = 1200;

	MemoryTile* tile1 = nullptr;
	MemoryTile* tile2 = nullptr;

	bool compareMode = false;
	float timeOfSecondClick = -1; // this is when the second click landed

	void Main();
	void Start();
	void Update();
	void Restart();
};