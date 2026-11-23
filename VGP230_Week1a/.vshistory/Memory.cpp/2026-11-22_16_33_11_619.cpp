#include "Memory.h"
#include <raylib.h>
#include <algorithm>


void Memory::Main()
{
	Start();
	InitWindow(widthHeight, widthHeight, "Memory");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		Update();
		EndDrawing();
	}
	CloseWindow();
}

void Memory::Start()
{
	int x = GAP;
	int y = GAP;

	int widthForTiles = widthHeight - (gridSize + 1) * GAP;
	int size = widthForTiles / gridSize;

	std::vector<int> numbers;
	for (int i = 0; i < gridSize * gridSize / 2; i++)
	{
		numbers.push_back(i + 1);
		numbers.push_back(i + 1);
	}

	// 1,1, 2,2, 3,3, 4,4, 5,5, 6,6, 7,7, 8,8
	for (int c = 0; c < gridSize; c++)
	{
		for (int r = 0; r < gridSize; r++)
		{
			int randomIndex = rand() % numbers.size();
			int n = numbers[randomIndex];

			MemoryTile tile = MemoryTile(x, y, size, n);
			tiles.push_back(tile);

			numbers.erase(numbers.begin() + randomIndex);

			x += GAP + size;
		}
		y += GAP + size;
		x = GAP;
	}

}

void Memory::Update()
{
	// make grid larger (up to 8x8)
	if (IsKeyPressed(KEY_UP))
	{
		if (gridSize < 8)
		{
			gridSize++;
			Restart();
		}
	}

	// make grid smaller (down to 2x2)
	if (IsKeyPressed(KEY_DOWN))
	{
		if (gridSize > 2)
		{
			gridSize--;
			Restart();
		}
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !compareMode)
	{
		for (int i = 0; i < tiles.size(); i++)
		{
			if (CheckCollisionPointRec(GetMousePosition(), tiles[i].rect))
			{
				if (tiles[i].status != HIDDEN) break;

				tiles[i].status = FLIPPED;

				if (tile1 == nullptr) // theres is no tile one just yet
				{
					tile1 = &tiles[i]; // this was the first click
				}
				else // theres been a click before, this is the 2nd click
				{
					tile2 = &tiles[i];
					compareMode = true;
					timeOfSecondClick = GetTime(); // register it was now that we clicked the 2nd time
				}
				break; // because if we landed on a tile, there is no way we would land on another
			}
		}
	}

	if (compareMode)
	{
		if (GetTime() > timeOfSecondClick + WAIT_TIME)
		{
			// now lets compare them
			if (tile1->number == tile2->number)
			{
				tile1->status = tile2->status = MATCHED;
			}
			else
			{
				tile1->status = tile2->status = HIDDEN;

			}

			tile1 = tile2 = nullptr;
			compareMode = false;
		}
	}


	for (MemoryTile tile : tiles)
	{
		tile.Draw();
	}

	// gridsize control display
	//DrawText("Grid Size: " + gridSize + "x" + gridSize, 10, 10, 25, WHITE);
	//DrawText("Up Arrow: Increase Grid Size", 10, 45, 20, LIGHTGRAY);
	//DrawText("Down Arrow: Decrease Grid Size", 10, 75, 20, LIGHTGRAY);
}

void Memory::Restart()
{
	/*tile1 = nullptr;
	tile2 = nullptr;

	compareMode = false;
	timeOfSecondClick = -1;

	tiles.clear();*/

	Start();
}