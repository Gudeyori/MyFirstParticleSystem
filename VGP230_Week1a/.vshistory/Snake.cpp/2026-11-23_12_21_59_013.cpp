#include "Snake.h"

void Snake::Main()
{
	Start();
	InitWindow(screenWidth, screenHeight, "Snake Game");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		
		if (gameOver)
		{
			GameOver();
		}
		else if (isPaused)
		{
			Pause();
		}
		else
		{
			Update();
		}

		EndDrawing();
	}
	CloseWindow();
}

void Snake::Start()
{
	// vertical lines
	for (int i = 0; i < screenWidth / TILE_SIZE + 1; i++)
	{
		float x = min.x + TILE_SIZE * i;
		Vector2 s = Vector2{ x, min.y };
		Vector2 e = Vector2{ x, max.y };

		Line line = Line(s, e);
		grid.push_back(line);
	}

	// horizontal lines
	for (int i = 0; i < screenHeight / TILE_SIZE + 1; i++)
	{
		float y = min.y + TILE_SIZE * i;
		Vector2 s = Vector2{ min.x, y };
		Vector2 e = Vector2{ max.x, y };

		Line line = Line(s, e);
		grid.push_back(line);
	}

	// Player
	Piece head;
	head.color = DARKPURPLE;

	Vector2 randomPosition = IndexToScreen(true);

	head.position = randomPosition;
	player.push_back(head);

	fruit.color = YELLOW;
	fruit.position = IndexToScreen(true); // it shouldnt be where the head or any pieces are
}

void Snake::Update()
{
	frameCount++;

	if (IsKeyPressed(KEY_P))
	{
		isPaused = !isPaused;
	}

	if (IsKeyPressed(KEY_R))
	{
		Restart();
	}

	if (IsKeyPressed(KEY_DOWN) && speed.y == 0)
	{
		speed = Vector2{ 0, TILE_SIZE };
	}

	if (IsKeyPressed(KEY_UP) && speed.y == 0)
	{
		speed = Vector2{ 0, -TILE_SIZE };
	}

	if (IsKeyPressed(KEY_RIGHT) && speed.x == 0)
	{
		speed = Vector2{ TILE_SIZE, 0 };
	}

	if (IsKeyPressed(KEY_LEFT) && speed.x == 0)
	{
		speed = Vector2{ -TILE_SIZE, 0 };
	}

	// player is a vector
	// of pieces, its got a head and tail (that we dont have)

	if (frameCount % 20 == 0)
	{
		for (int i = player.size() - 1; i > 0; i--)
		{
			player[i].position = player[i - 1].position;
		}

		// move the head
		player[0].position += speed;

		if (fruitCount > 0 && (fruitCount + 1) % 10 == 0)
		{
			fruit.color = RED;
		}
		else
		{
			fruit.color = YELLOW;
		}

		if (player[0].position == fruit.position) // ran into a fruit
		{
			fruitCount++;
			Piece tail;
			tail.color = PURPLE;
			tail.position = player[player.size() - 1].position;
			player.push_back(tail);
			fruit.position = IndexToScreen(true);
		}
	}

	for (Piece p : player)
	{
		p.Draw();
	}

	fruit.Draw();

	for (Line l : grid)
	{
		l.Draw();
	}
}

void Snake::DisplayScreenText(std::string text1, std::string text2)
{
	std::string text = text1;
	std::string subText = text2;

	int fontSize = 76;
	int subFontSize = fontSize / 2;

	int textWidth = MeasureText(text.c_str(), fontSize);
	int halfTextWidth = textWidth / 2;

	int subTextWidth = MeasureText(subText.c_str(), subFontSize);
	int halfSubTextWidth = subTextWidth / 2;

	int halfWidth = screenWidth / 2;
	int halfHeight = screenHeight / 2;
	int halfFontSize = fontSize / 2;

	int padding = halfFontSize + 20;

	DrawText(text.c_str(), halfWidth - halfTextWidth, halfHeight - halfFontSize, fontSize, WHITE);
	DrawText(subText.c_str(), halfWidth - halfSubTextWidth, halfHeight + padding, subFontSize, GRAY);
}

void Snake::Pause()
{
	DisplayScreenText("PAUSE!", "PRESS 'P' TO CONTINUE");
}

void Snake::GameOver()
{
	DisplayScreenText("GAME OVER!", "PRESS 'R' TO RESTART");

	if (IsKeyPressed(KEY_R))
	{
		Restart();
	}
}

void Snake::Restart()
{
	player.clear();

	Piece head;
	head.color = DARKPURPLE;
	head.position = IndexToScreen(true);

	player.push_back(head);

	frameCount = 0;
	fruitCount = 0;

	fruit.position = IndexToScreen(true);

	speed = Vector2{ 0, TILE_SIZE };

	isPaused = false;
	gameOver = false;
}