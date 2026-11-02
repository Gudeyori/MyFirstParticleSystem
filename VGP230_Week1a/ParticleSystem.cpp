#include "ParticleSystem.h"
#include "raylib.h"

Color RandomColor2()
{
	return Color{
		(unsigned char)GetRandomValue(0, 255),
		(unsigned char)GetRandomValue(0, 255),
		(unsigned char)GetRandomValue(0, 255),
		255
	};
}

void ParticleSystem::Main()
{
	Start();

	InitWindow(500, 500, "My Neato-Burrito Game");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		BeginBlendMode(BLEND_ADDITIVE);
		Update();
		EndBlendMode();

		EndDrawing();
	}

	CloseWindow();
	
}

void ParticleSystem::Start()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		Particle part = Particle(); // primary construction
		pool.push_back(part);
	}
}

// there is a pool with 1000 objects of the type particle
// they all are in the same spot and all are red

void ParticleSystem::Update()
{
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		int rate = GetRandomValue(3, 20);

		for (int r = 0; r < rate; r++)
		{
			for (int i = 0; i < pool.size(); i++)
			{
				if (!pool[i].active)
				{
					pool[i].Activate(GetMousePosition(),
						GetRandomValue(5, 50),
						RandomColor2(),
						GetRandomValue(2, 8),
						GetRandomValue(0, 360));

					break;
				}
			}
		}
	}


	for (int i = 0; i < pool.size(); i++)
		pool[i].Update();


	for (int i = 0; i < pool.size(); i++)
		pool[i].Draw();
}