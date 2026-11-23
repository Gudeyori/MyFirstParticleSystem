#pragma once
#include <vector>
#include <raylib.h>
#include <raymath.h>
#include <tuple>

class Snake
{
public:
	// think of ENUM as an expanded boolean
	// define is like static const
#define TILE_SIZE 71

	static const int screenWidth = 800;
	static const int screenHeight = 800;

	// this tells us if you fit x number of things horizontal and vertical 
	// how much space is extra on the right and bottom
	Vector2 borderGap = Vector2{ screenWidth % TILE_SIZE, screenHeight % TILE_SIZE };

	int maxRow = (screenWidth / TILE_SIZE) - 1;
	int maxCol = (screenHeight / TILE_SIZE) - 1;

	Vector2 min = Vector2{ borderGap.x / 2, borderGap.y / 2 };
	Vector2 max = Vector2{ screenWidth - borderGap.x / 2, screenHeight - borderGap.y / 2 };

	// Vector2Zero = Vector2 { 0, 0 }
	Vector2 IndexToScreen(bool random = false, int r = -1, int c = -1)
	{
		std::tuple <int, int> rowCol{0,0};
		if (random)
		{
			get<0>(rowCol) = GetRandomValue(0, maxRow);
			get<1>(rowCol) = GetRandomValue(0, maxCol);
		}
		else
		{
			get<0>(rowCol) = r;
			get<1>(rowCol) = c;
		}

		// if index is invalid
		if (get<0>(rowCol) > maxRow || get<1>(rowCol) > maxCol || get<0>(rowCol) < 0 || get<1>(rowCol) < 0)
		{
			return Vector2{ 0, 0 };
		}

		float x = min.x + get<0>(rowCol) * TILE_SIZE;
		float y = min.y + get<1>(rowCol) * TILE_SIZE;

		return Vector2(x, y);
	}

	struct Line
	{
		Vector2 start, end; // this is declaring multiple variables that are the same type

		Line(Vector2 s, Vector2 e)
		{
			this->start = s;
			this->end = e;
		}

		void Draw()
		{ 
			DrawLineV(start, end, GRAY);
		}
	};

	std::vector<Line> grid;

	struct Piece
	{
		Vector2 position = Vector2{ 0, 0}; // top left
		Vector2 size = Vector2{ TILE_SIZE, TILE_SIZE };
		Color color = WHITE;

		void Draw()
		{
			DrawRectangleV(position, size, color);
		}
	};

	std::vector<Piece> player;
	Vector2 speed = Vector2{ 0, TILE_SIZE };
	int frameCount = 0;

	Piece fruit;
	int fruitCount = 0;

	void Main(); // the raylib stuff
	void Start(); // where starting stuff goes
	void Update(); // frame by frame calculation

	bool isPaused = false;
};