#include "Snake.h"

void Snake::Main()
{
	Start();
	InitWindow(screenWidth, screenHeight, "Snake Game");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{

		if (!gameOver && IsKeyPressed(KEY_P))
		{
			isPaused = !isPaused;
		}

		// gameOver && 
		if (IsKeyPressed(KEY_R))
		{
			Restart();
		}

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
	SpawnFruit();
}

void Snake::Update()
{
	frameCount++;
	
	if (movementOverride == true)
	{
		if (GetTime() - movementOverrideStartTime >= 10.0)
		{
			movementOverride = false;
		}
	}

	if (movementOverride == false)
	{
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
	}
	else
	{
		Vector2 head = player[0].position;
		Vector2 fruitPiece = fruit.position;

		// move head to fruitPiece.x first
		if (head.x > fruitPiece.x)
		{
			head.x -= TILE_SIZE;
		}

		if (head.x == fruitPiece.x)
		{
			// go up
			if (head.y > fruitPiece.y)
			{
				head.y -= TILE_SIZE;
			}
			else
			{
				// go down
				head.y += TILE_SIZE;
			}
		}
	}

	// draw a line that follows the grid
	// from head to fruit
	if (IsKeyDown(KEY_C))
	{
		Vector2 head = player[0].position;
		Vector2 fruitPiece = fruit.position;

		// draw the horizontal line
		DrawLine(head.x + TILE_SIZE / 2, head.y + TILE_SIZE / 2,
			fruitPiece.x + TILE_SIZE / 2, head.y + TILE_SIZE / 2, RED);

		// then vertical line
		DrawLine(fruitPiece.x + TILE_SIZE / 2, head.y + TILE_SIZE / 2,
			fruitPiece.x + TILE_SIZE / 2, fruitPiece.y + TILE_SIZE / 2, RED);
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

		// check if the head collides with a border
		if (player[0].position.x < min.x || player[0].position.y < min.y
			|| player[0].position.x > max.x || player[0].position.y > max.y)
		{
			gameOver = true;
			return;
		}

		// check if the head hits its own body
		// i starts at 1 because head is index 0!
		for (int i = 1; i < player.size(); i++)
		{
			if (player[0].position.x == player[i].position.x &&
				player[0].position.y == player[i].position.y)
			{
				gameOver = true;

				// dont need to keep checking pieces if game is already over
				break;
			}
		}

		if (fruitCount > 0 && (fruitCount + 1) % 10 == 0)
		{
			fruit.color = SKYBLUE;
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
			SpawnFruit();
		}

		if (fruitCount > 0 && fruitCount % 10 == 0 && !gameOver)
		{
			movementOverride = true;
			movementOverrideStartTime = GetTime();
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

void Snake::SpawnFruit()
{
	bool isOverlapping;

	do
	{
		isOverlapping = false;
		fruit.position = IndexToScreen(true);

		for (int i = 0; i < player.size(); i++)
		{
			if (fruit.position.x == player[i].position.x &&
				fruit.position.y == player[i].position.y)
			{
				isOverlapping = true;
				break;
			}
		}

	} while (isOverlapping);
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

	SpawnFruit();

	speed = Vector2{ 0, TILE_SIZE };

	isPaused = false;
	gameOver = false;
}