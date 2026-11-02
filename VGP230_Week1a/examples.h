#pragma once
#include <raylib.h>
#include <iostream>
#include <string>
#include <random>
#include <raymath.h>
#include <vector>

void TemplateFunc()
{
	InitWindow(500, 500, "My Neato-Burrito Game");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		EndDrawing();
	}

	CloseWindow();
}

void FirstDrawing()
{
	InitWindow(500, 500, "My Neato-Burrito Game");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		std::string txt = "Yori";

		// x and y co-ordinate for center of circles
		int xCenter = 500 / 2;
		int yCenter = 500 / 2;

		// radius of circles
		int r = 150;

		// circle 1: draws a BLACK circle at [250, 250]
		// the radius is 150 + 70 units long
		DrawCircle(xCenter, yCenter, r + 20, BLACK);

		// circle 2: draws a BLUE circle at [250, 250] on TOP of circle 1
		// has a smaller radius, only 150 units
		DrawCircle(xCenter, yCenter, r, BLUE);

		// vector2 turns seperate x and y co-ordinates into a single point as a variable
		Vector2 center = Vector2{ (float)xCenter, (float)yCenter };

		// at the center, draw a 5 sided polygod in RED
		// -18 refers to the rotation so that the point is up
		DrawPoly(center, 5, r, -18, RED);

		// this draws lines AROUND the RED polygon in BLACK
		// 20 refers to the thickness of the lines
		DrawPolyLinesEx(center, 5, r, -18, 20, BLACK);

		int fontSize = 60;
		int txtWidth = MeasureText(txt.c_str(), fontSize);
		int halfTextWidth = txtWidth / 2;

		int txtCenx = xCenter - halfTextWidth;
		int txtCeny = yCenter - fontSize / 2;

		// same as before, draws text at [x, y] in YELLOW at a specific font size
		DrawText(txt.c_str(), txtCenx, txtCeny, fontSize, YELLOW);


		EndDrawing();
	}

	CloseWindow();
}

void MovingBall()
{
	int width = 800;
	int height = 500;

	InitWindow(width, height, "Bouncing Ball");

	int r = 50;
	int speed = 2;
	int cenX = r;
	int cenY = height / 2;
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		for (int i = 10; i > 0; i--)
		{
			DrawCircle(cenX - i * speed * 25, cenY, r, Color{ 0,0,255, (unsigned char)(255 - 25 * i) });
		}

		DrawCircle(cenX, cenY, r, DARKPURPLE);
		cenX += speed;

		if (cenX > width + r)
		{
			cenX = -r + 1;
		}

		EndDrawing();
	}

	CloseWindow();
}

void PoofBall()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> randomAngle(-2, 2);

	int width = 500;
	int height = 500;

	InitWindow(width, height, "Poof Ball");
	SetTargetFPS(60);

	// ball 1
	int r = 20;
	int cenX = r;
	int cenY = height / 2;

	int xSpeed = 15;
	int ySpeed = 15;

	//ball 2
	int r2 = 20;
	int cenX2 = 480;
	int cenY2 = 20;


	int xSpeed2 = 10;
	int ySpeed2 = 10;

	bool collided = false;

	while (!WindowShouldClose())
	{
		// move
		cenX += xSpeed;
		cenY += ySpeed;

		cenX2 += xSpeed2;
		cenY2 += ySpeed2;

		// ball 1
		// if the ball hits the bottom or top
		if ((cenY + r) > height || (cenY - r) < 0)
		{
			// reverse the direction the ball is travelling
			ySpeed = -ySpeed;

			// change the angle the ball is travelling
			xSpeed += randomAngle(gen);
		}

		// ball 1
		// if the ball hits the left or the right
		if ((cenX + r) > width || (cenX - r) < 0)
		{
			// reverse the direction the ball is travelling
			xSpeed = -xSpeed;

			// change the angle the ball is travelling
			ySpeed += randomAngle(gen);
		}

		// ball 2
		// if the ball hits the bottom or top
		if ((cenY2 + r2) > height || (cenY2 - r2) < 0)
		{
			// reverse the direction the ball is travelling
			ySpeed2 = -ySpeed2;

			// change the angle the ball is travelling
			xSpeed2 += randomAngle(gen);
		}

		// ball 2
		// if the ball hits the left or the right
		if ((cenX2 + r2) > width || (cenX2 - r2) < 0)
		{
			// reverse the direction the ball is travelling
			xSpeed2 = -xSpeed2;

			// change the angle the ball is travelling
			ySpeed2 += randomAngle(gen);
		}

		// turn the sets of x and y into points
		Vector2 balla = { (float)cenX, (float)cenY };
		Vector2 ballb = { (float)cenX2, (float)cenY2 };

		// put those points into the distance formula
		int distance = Vector2Distance(balla, ballb);

		// did they collide?
		if (distance <= r + r2)
		{
			collided = true;
			std::cout << "\nWE TOUCHIED!";
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);

		if (!collided)
		{
			DrawCircle(cenX, cenY, r, DARKPURPLE);

			DrawCircle(cenX2, cenY2, r2, DARKGRAY);
		}

		EndDrawing();
	}

	CloseWindow();
}

void TriangleFunc()
{
	int wh = 800;
	InitWindow(wh, wh, "My Neato-Burrito Game");
	SetTargetFPS(60);

	Vector2 top = Vector2{ (float)wh / 2, 100 };
	Vector2 left = Vector2{ 100, (float)wh - 100 };
	Vector2 right = Vector2{ (float)wh - 100, (float)wh - 100 };

	float r = 20;

	int isDragging = 0; // none

	while (!WindowShouldClose())
	{
		Vector2 mouse = GetMousePosition();
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			// the distnace of the mouse position against the top circle
			float topDist = Vector2Distance(mouse, top);
			float leftDist = Vector2Distance(mouse, left);
			float rightDist = Vector2Distance(mouse, right);

			if (topDist < r) isDragging = 1;
			else if (leftDist < r) isDragging = 2;
			else if (rightDist < r) isDragging = 3;


			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) isDragging = 0;

			switch (isDragging)
			{
			case 1: top = mouse; break;
			case 2: left = mouse; break;
			case 3: right = mouse; break;
			default:
				break;
			}
		}

		BeginDrawing();
		ClearBackground(GRAY);

		DrawTriangleLines(left, right, top, BLACK);

		DrawCircleV(top, r, BLUE);
		DrawCircleV(left, r, GREEN);
		DrawCircleV(right, r, YELLOW);

		EndDrawing();
	}

	CloseWindow();
}

void ColorAdditionFun()
{
	int wh = 800;
	InitWindow(wh, wh, "My Neato-Burrito Game");
	SetTargetFPS(60);

	float gap = 200;

	float x2 = wh / 2 - 100; float y2 = wh / 2;
	float x3 = wh / 2 + 100; float y3 = wh / 2;

	Vector2 top = Vector2{ (float)wh / 2, (float)wh / 2 - 100 };
	Vector2 left = Vector2{ x2, y2 };
	Vector2 right = Vector2{ x3, y3 };

	float r = 200;
	float inc = 1;

	while (!WindowShouldClose())
	{

		Vector2 mouse = GetMousePosition();
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			float topDist = Vector2Distance(mouse, top);

			if (topDist < r)
			{
				top = mouse;

				// left
				float angle2 = 30;
				x2 -= cos(DEG2RAD * angle2) * inc;
				y2 -= sin(DEG2RAD * angle2) * inc;

				// right
				float angle3 = 30;
				x3 += cos(DEG2RAD * angle3) * inc;
				y3 += sin(DEG2RAD * angle3) * inc;
			}
		}

		BeginDrawing();
		ClearBackground(BLACK);

		DrawTriangleLines(left, right, top, RAYWHITE);

		BeginBlendMode(BLEND_ADDITIVE);
		DrawCircleV(right, r, YELLOW);
		DrawCircleV(left, r, GREEN);
		DrawCircleV(top, r, BLUE);
		EndBlendMode();

		EndDrawing();
	}

	CloseWindow();
}

//void ColorfulOctogon()
//{
//	InitWindow(800, 800, "My Neato-Burrito Game");
//	SetTargetFPS(60);
//
//	std::vector<Vector2> corners;
//	Vector2 cen = { 400, 400 };
//
//	float r = 200;
//
//	int sides = 8;
//	float incA = 360/((float)sides);
//
//	for (int i = 0; i < sides; i++)
//	{
//		float x = cen.x + (cos(DEG2RAD * incA * i) * r);
//		float y = cen.y + (sin(DEG2RAD * incA * i) * r);
//
//		corners.push_back(Vector2{ x, y });
//	}
//
//	// here, you have an array with 8 points that represent points one to eight
//
//	std::vector<Color> colors{ RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, PINK, RAYWHITE };
//
//	while (!WindowShouldClose())
//	{
//		BeginDrawing();
//		ClearBackground(BLACK);
//
//
//		for (int i = 0; i < sides - 1; i++)
//		{
//			DrawTriangle(cen, corners[i+1], corners[i], colors[i]);
//		}
//
//		EndDrawing();
//	}
//
//	CloseWindow();
//}

void ColorfulOctogon()
{
	InitWindow(500, 500, "My Neato-Burrito Game");
	SetTargetFPS(60);

	float x = 250.0f;
	float y = 250.0f;

	Vector2 center = { x, y };

	int sides = 8;
	int radius = 200;

	float angle = 360 / sides;

	//std::vector<Color> colors = { RED, ORANGE, YELLOW, GREEN, DARKBLUE, PURPLE, PINK, WHITE };
	std::vector<Vector2> points;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLUE);

		for (int i = 0; i < sides; i++)
		{
			float alpha = i * angle * DEG2RAD;
			float x = center.x + cos(alpha) * radius;
			float y = center.y + sin(alpha) * radius;

			Vector2 point = { x, y };
			points.push_back(point);
		}

		for (int i = 0; i < sides - 1; i++)
		{
			DrawTriangle(center, points[i + 1], points[i], BLACK);
		}

		DrawTriangle(center, points[0], points[points.size() - 1], BLACK);

		EndDrawing();
	}

	CloseWindow();
}

void CollisionFunction()
{

	Rectangle rectA = Rectangle{ 100, 400, 300, 50 };
	Rectangle rectB = Rectangle{ 225, 50, 50, 50 };
	Rectangle rectC = Rectangle{ 295, 50, 50, 50 };
	int velocity = 2;
	bool collision = false;

	// button state colors
	Color normalColor = Color{ 40, 115, 235, 255 };
	Color hoverColor = Color{ 5, 21, 247, 255 };
	Color clickedColor = Color{ 189, 120, 9, 255 };
	Color shadowColor = Color{ 41, 41, 41, 255 };

	// x, y, width, height
	Rectangle buttonRect = Rectangle{ 50, 50, 150, 44 };
	Color currentColor = normalColor;

	InitWindow(500, 500, "Collision Test");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		// as we go forward
		// i wanna make sure the value for box b increases	


		rectB.y += velocity;
		rectC.height += velocity;

		BeginDrawing();
		ClearBackground(Color{ 20, 20, 20, 255 });

		// right ARROW
		if (IsKeyDown(KEY_RIGHT))
		{
			rectA.x += velocity;
		}
		// left ARROW
		else if (IsKeyDown(KEY_LEFT))
		{
			rectA.x -= velocity;
		}

		// this is the same as the next, but below is more readable
		// collision = CheckCollisionRecs(rectA, rectB) || CheckCollisionRecs(rectA, rectC)

		// CheckCollisionRecs is a bool!
		if (CheckCollisionRecs(rectA, rectB) || CheckCollisionRecs(rectA, rectC))
		{
			collision = true;
		}
		else
		{
			collision = false;
		}

		if (collision)
		{
			int textWidth = MeasureText("They Collided", 50);
			DrawText("They Collided", 250 - textWidth / 2, 250 - 25, 50, WHITE);
		}

		// i wanna draw rectA
		DrawRectangleRec(rectA, YELLOW);

		// i wanna draw rectB
		DrawRectangleRec(rectB, RED);
		DrawRectangleRec(rectC, BLUE);


		if (CheckCollisionPointRec(GetMousePosition(), buttonRect))
		{
			currentColor = hoverColor;
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				currentColor = clickedColor;
			}
		}
		else
		{
			currentColor = normalColor;
		}

		// roundness is the arc between these points. 1 is a 100% arc. its how ROUND is the corner
		// segments is the amount of points on the curve, determines how SMOOTH the corner is
		DrawRectangleRounded(buttonRect, 0.35, 12, currentColor);
		int textWidth = MeasureText("Click", 24);
		int fontSize = 24;

		// these numbers come from the position of the button
		DrawText("Click", 125 - textWidth / 2, 72 - fontSize / 2, fontSize, BLACK);


		EndDrawing();
	}

	CloseWindow();
}

int main()
{
	//FirstDrawing();
	//MovingBall();
	//PoofBall();

	// week 2 and broken
	//TriangleFunc();
	//ColorAdditionFun();
	//ColorfulOctogon();

	//CollisionFunction();
}