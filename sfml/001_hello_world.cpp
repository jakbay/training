#include <SFML/Graphics.hpp>
int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Application");
	sf::CircleShape shape;
	shape.setRadius(40.f);
	shape.setPosition(130.f, 50.f);
	shape.setFillColor(sf::Color::Red);
	sf::CircleShape shape2;
	shape2.setRadius(100.f);
	shape2.setPosition(400.f, 200.f);
	shape2.setFillColor(sf::Color::Blue);
	sf::CircleShape shape3;
	shape3.setRadius(75.f);
	shape3.setPosition(500.f, 100.f);
	shape3.setFillColor(sf::Color::Green);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(shape);
		window.draw(shape2);
		window.draw(shape3);
		window.display();
	}
	return 0;
}
