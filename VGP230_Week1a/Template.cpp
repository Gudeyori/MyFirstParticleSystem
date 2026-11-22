#include "Template.h"

void Template::Main()
{
	Start();
	InitWindow(800, 800, "Template");
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

void Template::Start()
{
}

void Template::Update()
{
}