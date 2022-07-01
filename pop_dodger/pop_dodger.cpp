#include <SFML/Graphics.hpp>
#include <windows.h>

using namespace sf;


void Stealt();


int Main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 20;

	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(500, 500), "SFML Works!");
	Stealt(); //hide console
	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				// тогда закрываем его
				window.close();
		}

		window.clear(Color(153, 204, 255));


		CircleShape circle(	50.f);
		
		circle.setFillColor(Color(250, 220, 100));

		circle.setOutlineThickness(15);
		circle.setOutlineColor(Color(0, 0, 0, 100));
		circle.move(15, 15);

		CircleShape triangle(65.f, 3);
		triangle.setPosition(125, 0); // устанавливаем начальную позицию справа от круга
		triangle.setFillColor(Color::Blue); // устанавливаем цвет треугольника - синий
		window.draw(triangle); // отрисовка треугольника

		// Создаем квадрат
		CircleShape square(60.f, 4);
		square.setPosition(250, 0); // устанавливаем начальную позицию справа от треугольника
		square.setFillColor(Color::Red); // устанавливаем цвет квадрата - красный
		window.draw(square); // отрисовка квадрата

		// Создаем октагон
		CircleShape octagon(60.f, 7);
		octagon.setPosition(380, 0); // устанавливаем начальную позицию справа от квадрата
		octagon.setFillColor(Color::Cyan); // устанавливаем цвет октагона - бирюзовый
		window.draw(octagon); // отрисовка октагона

		// Заготовка фигуры многоугольника 
		ConvexShape convex;

		// Устанавливаем ему 5 вершин
		convex.setPointCount(5);

		// Устанавливаем координаты вершин
		convex.setPoint(0, Vector2f(0.f, 0.f));
		convex.setPoint(1, Vector2f(150.f, 10.f));
		convex.setPoint(2, Vector2f(120.f, 90.f));
		convex.setPoint(3, Vector2f(30.f, 100.f));
		convex.setPoint(4, Vector2f(5.f, 50.f));

		// Устанавливаем цвет многоугольника - черный
		convex.setFillColor(Color::Black);

		// Теперь сдвинем его вниз и чуть-чуть вправо
		convex.move(1, 150);

		// Отрисовка многоугольника
		window.draw(convex);

		// Создаем прямоугольник размером 70х100
		RectangleShape rectangle(Vector2f(70.f, 100.f));

		// Перемещаем его в нижний ряд справа от многоугольника
		rectangle.move(160, 150);

		// Устанавливаем ему цвет
		rectangle.setFillColor(Color(175, 180, 240));

		// Отрисовка прямоугольника
		window.draw(rectangle);

		// Линия с заданной толщиной
		RectangleShape line_with_thickness(Vector2f(130.f, 5.f));

		// Поворачиваем её на 45 градусов
		line_with_thickness.rotate(30.f);

		// Устанавливаем цвет
		line_with_thickness.setFillColor(Color(Color::Magenta));

		// Перемещаем её в нижний ряд справа от прямоугольника
		line_with_thickness.move(250, 150);

		// Отрисовка линии
		window.draw(line_with_thickness);


		window.draw(circle);
		window.display();
	}

	return 0;
}

void Stealt()
{
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
}
