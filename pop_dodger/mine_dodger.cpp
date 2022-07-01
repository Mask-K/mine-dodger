#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <windows.h>

using namespace sf;

void Stealth();

bool isMinePossible(int logic[][12], int i, int j);

int main()
{
	std::random_device rd; 
	std::mt19937 mersenne(rd()); // generate random numbers using Medison's vortex

	Stealth(); //hide console window

	RenderWindow app(VideoMode(400, 400), "Mines dodger"); // main window of the app

	//std::cout << "What size?";

	int width = 32; //cell's width
	int gridLogic[12][12]; // logic of game
	int gridView[12][12]; // what we actually see

	Texture t;
	t.loadFromFile(R"(D:\Програмування\CumBack\pop_dodger\x64\Debug\tiles.jpg)"); // making texture + sprite
	Sprite s(t);

	for (int i = 1; i <= 10; i++) // randomly deside what cell will have a mine
		for (int j = 1; j <= 10; j++)
		{
			gridView[i][j] = 10;
			if (mersenne() % 5 == 0 && isMinePossible(gridLogic, i, j))  gridLogic[i][j] = 9;
			else gridLogic[i][j] = 0;
		}

	for (int i = 1; i <= 10; i++) // fill logic grid with apropriate numbers
		for (int j = 1; j <= 10; j++)
		{
			int n = 0;
			if (gridLogic[i][j] == 9) continue;
			if (gridLogic[i + 1][j] == 9) n++;
			if (gridLogic[i][j + 1] == 9) n++;
			if (gridLogic[i - 1][j] == 9) n++;
			if (gridLogic[i][j - 1] == 9) n++;
			if (gridLogic[i + 1][j + 1] == 9) n++;
			if (gridLogic[i - 1][j - 1] == 9) n++;
			if (gridLogic[i - 1][j + 1] == 9) n++;
			if (gridLogic[i + 1][j - 1] == 9) n++;
			gridLogic[i][j] = n;
		}

	while (app.isOpen())
	{
		Vector2i pos = Mouse::getPosition(app); // find the position of mouse when clicking
		int x = pos.x / width;
		int y = pos.y / width;

		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();

			if (e.type == Event::MouseButtonPressed) // if mouse click
				if (e.key.code == Mouse::Left) gridView[x][y] = gridLogic[x][y];
				else if (e.key.code == Mouse::Right) {
					if (gridView[x][y] == 10)
						gridView[x][y] = 11;
					else if(gridView[x][y] == 11)
						gridView[x][y] = 10;
				}
		}

		app.clear(Color::White); // white background

		for (int i = 1; i <= 10; i++)
			for (int j = 1; j <= 10; j++)
			{
				if (x > 0 && y > 0 && gridView[x][y] == 9) {
					gridView[i][j] = gridLogic[i][j];
				}

				s.setTextureRect(IntRect(gridView[i][j] * width, 0, width, width)); // get concrete sprite

				s.setPosition(i * width, j * width); // insert obtained sprite

				app.draw(s); // draw it
			}
		app.display(); // display whole window
	}

	return 0;
}

void Stealth()
{
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
}

bool isMinePossible(int logic[][12], int i, int j) {
	if (i == 2 && i == j && logic[1][1] == 9 && logic[1][2] == 9 && logic[2][1] == 9)
		return false;
	if (i == 11 && j == 2 && logic[10][1] == 9 && logic[10][2] == 9 && logic[11][1] == 9)
		return false;
	if (i == 11 && j == 11 && logic[10][10] == 9 && logic[10][11] == 9 && logic[11][10 == 9])
		return false;
	if (i == 2 && j == 11 && logic[1][10] == 9 && logic[1][11] == 9 && logic[2][10] == 9)
		return false;
	if (i == 2 && j > 2 && logic[i - 1][j - 2] == 9 && logic[i - 1][j - 1] == 9 && logic[i - 1][j] == 9 
		&& logic[i][j - 2] == 9 && logic[i][j - 1] == 9)
		return false;
	if (i == 11 && j > 2 && logic[i - 1][j - 2] == 9 && logic[i - 1][j - 1] == 9 && logic[i - 1][j] == 9
		&& logic[i][j - 2] == 9 && logic[i][j - 1] == 9)
		return false;
	if (j == 2 && i > 2 && logic[i - 2][j - 1] == 9 && logic[i - 2][j] == 9 && logic[i - 1][j - 1] == 9 
		&& logic[i - 1][j] == 9 && logic[i][j - 1] == 9)
		return false;
	if (j == 1 && i > 2 && logic[i - 2][j - 1] == 9 && logic[i - 2][j] == 9 && logic[i - 1][j - 1] == 9
		&& logic[i - 1][j] == 9 && logic[i][j - 1] == 9)
		return false;
	if (i > 2 && j > 2 && i < 10 && j < 10 && logic[i - 2][j - 2] == 9 && logic[i - 2][j - 1] == 9 && logic[i - 2][j] == 9 
		&& logic[i - 1][j - 2] == 9 && logic[i - 1][j - 1] == 9 && logic[i - 1][j] == 9 
		&& logic[i][j - 2] == 9 && logic[i][j - 1] == 9)
		return false;

	return true;
}