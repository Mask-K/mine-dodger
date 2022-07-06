#include "Menu.h"
#include <windows.h>
#include "Grid.h"

#include <exception>
#include <iostream>

using namespace sf;

const int N = 10;

void Stealth();

int main()
{
	

	Stealth(); //hide console window

	RenderWindow app(VideoMode(384, 384), "Mines dodger"); // main window of the app

	Menu menu(app.getSize().x - 50, app.getSize().y);
	bool notplay = true;
	while (app.isOpen() && notplay)
	{
		sf::Event event;
		while (app.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						notplay = false;
						break;
					
					case 1:
						app.close();
						break;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				app.close();

				break;

			}
		}

		app.clear(Color(102, 204, 255));

		menu.draw(app);

		app.display();
	}


	int width = 32; //cell's width
	bool helper = true;
	

	Texture t;
	t.loadFromFile(R"(D:\Програмування\CumBack\pop_dodger\x64\Debug\tiles.jpg)"); // making texture + sprite
	Sprite s(t);

	Font f;
	f.loadFromFile(R"(D:\Програмування\CumBack\pop_dodger\x64\Debug\font.ttf)");
	Text text;
	text.setFont(f);
	text.setCharacterSize(24);
	text.setFillColor(Color::Black);
	text.setStyle(Text::Bold);
	text.setString("Game Over!");
	text.setPosition(132, 0);
	Grid gr(N);
	int flags{};
	
		while (app.isOpen())
		{
			Vector2i pos = Mouse::getPosition(app); // find the position of mouse when clicking
			int x = pos.x / width - 1;
			int y = pos.y / width - 1;


			if (helper) {
				Event e;
				while (app.pollEvent(e))
				{
					if (e.type == Event::Closed)
						app.close();

					if (e.type == Event::MouseButtonPressed && x >= 0 && y >= 0 && x < N && y < N) // if mouse click
						if (e.key.code == Mouse::Left) {
							if (gr.getView(x, y) == 10) {
								if (!gr.getLogic(x, y)) // if empty cell, we need to show all nearby
									gr.showUp(x, y);
								else if (gr.getView(x, y) != 11) { // if flag - we do nothing
									gr.border(x, y);
								}
							}
						}
						else if (e.key.code == Mouse::Right) {
							if (gr.getView(x, y) == 10 && flags < 2 * N) {
								gr.setView(x, y, 11);
								++flags;
							}
							else if (gr.getView(x, y) == 11) {
								gr.setView(x, y, 10);
								--flags;
							}
						}
				}

				app.clear(Color(102, 204, 255)); // white background

				for (int i = 0; i < N; i++)
					for (int j = 0; j < N; j++)
					{
						if (x >= 0 && y >= 0 && x < N && y < N && gr.getView(x, y) == 9 && gr.getLogic(i, j) == 9) {
							gr.setView(i, j);
						}

						s.setTextureRect(IntRect(gr.getView(i, j) * width, 0, width, width)); // get concrete sprite

						s.setPosition((i + 1) * width, (j + 1) * width); // insert obtained sprite

						app.draw(s); // draw it
					}

				if (x >= 0 && y >= 0 && x < N && y < N && gr.getView(x, y) == 9) {
					helper = false;
					app.draw(text);

				}
				else if (flags == 2 * N && gr.isComplete()) {
					helper = false;
					text.setString("You won!");
					app.draw(text);
				}
				app.display(); // display whole window
			}

			if (!helper) { // premission to close app
				Event e;
				while (app.pollEvent(e))
				{
					if (e.type == Event::Closed)
						app.close();
				}
			}

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

