#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <windows.h>
#include <vector>

using namespace sf;

const int N = 10;

void Stealth();

bool isMinePossible(int (*logic)[N], int i, int j);

void showUp(int (* view)[N], int (* logic)[N], int i, int j);

void border(int(*view)[N], int(*logic)[N], int i, int j);

int main()
{
	std::random_device rd; 
	std::mt19937 mersenne(rd()); // generate random numbers using Medison's vortex

	Stealth(); //hide console window

	RenderWindow app(VideoMode(400, 400), "Mines dodger"); // main window of the app


	int width = 32; //cell's width
	std::vector<int> a(N);
	int gridLogic[N][N]; // logic of game
	int gridView[N][N]; // what we actually see

	Texture t;
	t.loadFromFile(R"(D:\Програмування\CumBack\pop_dodger\x64\Debug\tiles.jpg)"); // making texture + sprite
	Sprite s(t);

	for (int i = 0; i < N; i++) // randomly deside what cell will have a mine
		for (int j = 0; j < N; j++)
		{
			gridView[i][j] = 10;
			if (mersenne() % 5 == 0 && isMinePossible(gridLogic, i, j))  gridLogic[i][j] = 9;
			else gridLogic[i][j] = 0;
		}

	for (int i = 0; i < N; i++) // fill logic grid with apropriate numbers
		for (int j = 0; j < N; j++)
		{
			int n = 0;
			if (gridLogic[i][j] == 9) continue;
			if (i < N - 1 && gridLogic[i + 1][j] == 9) n++;
			if (j < N - 1 && gridLogic[i][j + 1] == 9) n++;
			if (i > 0 && gridLogic[i - 1][j] == 9) n++;
			if (j > 0 && gridLogic[i][j - 1] == 9) n++;
			if (i < N - 1 && j < N - 1 && gridLogic[i + 1][j + 1] == 9) n++;
			if (i > 0 && j > 0 && gridLogic[i - 1][j - 1] == 9) n++;
			if (i > 0 && j < N - 1 && gridLogic[i - 1][j + 1] == 9) n++;
			if (i < N - 1 && j > 0 && gridLogic[i + 1][j - 1] == 9) n++;
			gridLogic[i][j] = n;
		}

	while (app.isOpen())
	{
		Vector2i pos = Mouse::getPosition(app); // find the position of mouse when clicking
		int x = pos.x / width - 1;
		int y = pos.y / width - 1;
		
		

		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();

			if (e.type == Event::MouseButtonPressed) // if mouse click
				if (e.key.code == Mouse::Left && gridView[x][y] == 10) {

					if (!gridLogic[x][y]) // if empty cell, we need to show all nearby
						showUp(gridView, gridLogic, x, y);
					else if (gridView[x][y] != 11) { // if flag - we do nothing
						border(gridView, gridLogic, x, y);
					}
				}
				else if (e.key.code == Mouse::Right) {
					if (gridView[x][y] == 10)
						gridView[x][y] = 11;
					else if(gridView[x][y] == 11)
						gridView[x][y] = 10;
				}
		}

		app.clear(Color::White); // white background

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				if (x >= 0 && y >= 0 && gridView[x][y] == 9 && gridLogic[i][j] == 9) {
					gridView[i][j] = gridLogic[i][j];
				}

				s.setTextureRect(IntRect(gridView[i][j] * width, 0, width, width)); // get concrete sprite

				s.setPosition((i + 1) * width, (j + 1) * width); // insert obtained sprite

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

bool isMinePossible(int (*logic)[N], int i, int j) {
	if (i == 1 && i == 1 && logic[i-1][j-1] == 9 && logic[i-1][j] == 9 && logic[i][j-1] == 9)
		return false;
	if (i == N-1 && j == 1 && logic[i-1][j-1] == 9 && logic[i-1][j] == 9 && logic[i][j-1] == 9)
		return false;
	if (i == N-1 && j == N - 1 && logic[i-1][j-1] == 9 && logic[i-1][j] == 9 && logic[i][j-1] == 9)
		return false;
	if (i == 1 && j == N-1 && logic[i-1][j-1] == 9 && logic[i-1][j] == 9 && logic[i][j-1] == 9)
		return false;
	if (i == 1 && j > 1 && logic[i - 1][j - 2] == 9 && logic[i - 1][j - 1] == 9 && logic[i - 1][j] == 9 
		&& logic[i][j - 2] == 9 && logic[i][j - 1] == 9)
		return false;
	if (i == N-1 && j > 1 && logic[i - 1][j - 2] == 9 && logic[i - 1][j - 1] == 9 && logic[i - 1][j] == 9
		&& logic[i][j - 2] == 9 && logic[i][j - 1] == 9)
		return false;
	if (j == 1 && i > 1 && logic[i - 2][j - 1] == 9 && logic[i - 2][j] == 9 && logic[i - 1][j - 1] == 9 
		&& logic[i - 1][j] == 9 && logic[i][j - 1] == 9)
		return false;
	if (j == N - 1 && i > 1 && logic[i - 2][j - 1] == 9 && logic[i - 2][j] == 9 && logic[i - 1][j - 1] == 9
		&& logic[i - 1][j] == 9 && logic[i][j - 1] == 9)
		return false;
	if (i > 1 && j > 1 && i < N-2 && j < N-2 && logic[i - 2][j - 2] == 9 && logic[i - 2][j - 1] == 9 && logic[i - 2][j] == 9 
		&& logic[i - 1][j - 2] == 9 && logic[i - 1][j - 1] == 9 && logic[i - 1][j] == 9 
		&& logic[i][j - 2] == 9 && logic[i][j - 1] == 9)
		return false;

	return true;
}

void showUp(int (*view)[N], int (*logic)[N], int i, int j) {
	if (i < 0 || j < 0 || i == N  || j == N  || view[i][j] != 10)
		return;
	view[i][j] = logic[i][j];
	if (!view[i][j]) {
		showUp(view, logic, i - 1, j - 1);
		showUp(view, logic, i - 1, j);
		showUp(view, logic, i - 1, j + 1);
		showUp(view, logic, i, j - 1);
		showUp(view, logic, i, j + 1);
		showUp(view, logic, i + 1, j - 1);
		showUp(view, logic, i + 1, j);
		showUp(view, logic, i + 1, j + 1);
	}
	return;
}

void border(int(*view)[N], int(*logic)[N], int i, int j) {
	view[i][j] = logic[i][j];
	if (i > 0 && j > 0 && !logic[i - 1][j - 1])
		showUp(view, logic, i - 1, j - 1);
	else if(i > 0 && !logic[i-1][j])
		showUp(view, logic, i - 1, j);
	else if(i > 0 && j < N - 1 && !logic[i-1][j+1])
		showUp(view, logic, i - 1, j + 1);
	else if(j > 0 && !logic[i][j-1])
		showUp(view, logic, i, j - 1);
	else if(j < N-1 && !logic[i][j+1])
		showUp(view, logic, i, j + 1);
	else if(i < N-1 && j > 0 && !logic[i+1][j-1])
		showUp(view, logic, i + 1, j - 1);
	else if(i < N-1 && !logic[i+1][j])
		showUp(view, logic, i + 1, j);
	else if(i < N-1 && j < N-1 && !logic[i+1][j+1])
		showUp(view, logic, i + 1, j + 1);
}