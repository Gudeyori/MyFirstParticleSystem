#include "MemoryTile.h"
#include <string>

void MemoryTile::Draw()
{
	int txtHeight = 40;
	std::string txt = "?";
	Color tileColor = YELLOW;
	int txtWidth = MeasureText(txt.c_str(), txtHeight);
	int txtX = rect.x + rect.width / 2 - (float)txtWidth / 2;
	int txtY = rect.y + rect.height / 2 - (float)txtHeight / 2;

	switch (status)
	{
	case HIDDEN:
	{
		break;
	}
	case FLIPPED:
	{
		tileColor = WHITE;
		txt = std::to_string(number);
		break;
	}
	case MATCHED:
	{
		tileColor = DARKPURPLE;
		txt = std::to_string(number);
		break;
	}
	}

	DrawRectangleRounded(rect, 0.25, 12, tileColor);
	DrawText(txt.c_str(), txtX, txtY, txtHeight, BLACK);
}

MemoryTile::MemoryTile(float x, float y, float size, int num)
{
	rect = Rectangle(x, y, size, size);
	this->number = num;
}