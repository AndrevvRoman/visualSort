#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <Windows.h>

using namespace sf;
using namespace std;


const int delay = 300;
Font font;



vector<int> createMas(int size)
{
	vector<int> mass(size);
	for (int i = 0; i < size; i++)
	{
		mass[i] = rand() % 31;
		cout << mass[i] << " ";
	}
	cout << endl;
	return mass;
}

void createField(RenderWindow &window, vector<int> &mass,vector<RectangleShape> &rect)
{
	
	Text numbers;
	numbers.setFont(font);
	numbers.setCharacterSize(22);
	numbers.setFillColor(Color::Black);

	for (int i = 0; i < rect.size(); i++)
	{
		rect[i].setFillColor(Color::White);
		rect[i].setSize(Vector2f(30, 30));
		rect[i].setPosition(Vector2f((i * 32) + 1, 0));

		numbers.setPosition(Vector2f((i * 32) + 4, 0));
		auto s = to_string(mass[i]);
		numbers.setString(s);
		
		window.draw(rect[i]);
		window.draw(numbers);
	}
	window.display();
	Sleep(delay);
}

void drawField(RenderWindow &window, vector<int> &mass, vector<RectangleShape> &rect)
{
	window.clear();

	Text numbers;
	numbers.setFont(font);
	numbers.setCharacterSize(22);
	numbers.setFillColor(Color::Black);

	for (int i = 0; i < mass.size(); i++)
	{

		numbers.setPosition(Vector2f((i * 32) + 4, 0));
		auto s = to_string(mass[i]);
		numbers.setString(s);

		window.draw(rect[i]);
		window.draw(numbers);
	}
	window.display();
	Sleep(delay);

}

void sort(RenderWindow &window, vector<int> &mass, vector<RectangleShape> &rect)
{
	bool flag = false;

	for (int i = 0; i < mass.size(); i++)
	{
		for (int j = 0; j < mass.size() - i - 1; j++)
		{
			rect[j].setFillColor(Color::Yellow);
			rect[j + 1].setFillColor(Color::Red);
			drawField(window, mass,rect);

			if (mass[j] > mass[j + 1])
			{

				swap(mass[j], mass[j + 1]);
				flag = true;
				rect[j].setFillColor(Color::Red);
				rect[j + 1].setFillColor(Color::Yellow);
				drawField(window,mass,rect);
			}
			rect[j].setFillColor(Color::White);
		}
		if (flag == false) break;
		else flag = false;
		rect[mass.size() - i - 1].setFillColor(Color::Green);
	}
	for (int i = 0; i < rect.size(); i++)
		rect[i].setFillColor(Color::Green);
	drawField(window,mass,rect);
}

int main()
{
	int size;
	cout << "Enter size: ";
	cin >> size;
	vector<int> mass = createMas(size);
	vector<RectangleShape> rect(size);

	if (!font.loadFromFile("arial.ttf"))
		cout << "Font didn't loaded!" << endl;
	
	RenderWindow window(VideoMode(800, 30), "Sort");
	
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
	}
	createField(window, mass,rect);
	sort(window, mass, rect);
	cout << "Done!" << endl;
	system("pause");

	return 0;
}