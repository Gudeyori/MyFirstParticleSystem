#pragma once
#include <raylib.h>
#include <vector>

enum MemoryTileStatus
{
	HIDDEN,
	FLIPPED,
	MATCHED
};

class MemoryTile
{
public:
	
	// x, y, w, h
	Rectangle rect;
	int number = 1;
	MemoryTileStatus status = HIDDEN;
	
	// c = column, r = row,
	MemoryTile(float x, float y, float size, int num);

	void Draw(const std::vector<Texture2D>& images, bool imageMode);
};