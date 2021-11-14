#include <SFML/Graphics.hpp>
#include <iostream>
#include "Shape.h"
#include <vector>
#include "Ball.h"
#include <memory>
#include "CollisionDetector.h"
#include "SpatialHash.h"

sf::IntRect WINDOW(
	{ 0,0 }, //Position
	{ 1080, 720 } //Size
);

int main()
{
	//Setup Scene
	sf::RenderWindow window(sf::VideoMode(WINDOW.width, WINDOW.height), "Circle Collision");
	std::unique_ptr<CollisionDetector> detector = std::make_unique<SpatialHash>(
		sf::Vector2f(WINDOW.left, WINDOW.top),
		sf::Vector2f(WINDOW.left + WINDOW.width, WINDOW.top + WINDOW.height),
		sf::Vector2i(50, 50) //must divide the size
	);

	std::vector<std::shared_ptr<Shape>> shapes;
	std::vector<std::shared_ptr<Entity>> entities;

	shapes.emplace_back(std::make_unique<Ball>(sf::Vector2f({ 120,230 })));
	entities.push_back(detector->addEntity(shapes.back()));
	entities.back()->getShape()->applyForce({ 500, 0 });
	entities.back()->getShape()->show(window);
	
	//Main loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == event.KeyReleased && event.key.code == sf::Keyboard::Q)
				window.close();
			else if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				std::cout << "Adding ball\n";

				shapes.emplace_back(std::make_unique<Ball>(sf::Vector2f({ 120,230 })));
				entities.push_back(detector->addEntity(shapes.back()));
				entities.back()->getShape()->applyForce({ 500, 0 });
				entities.back()->getShape()->show(window);
			}

		}

		window.clear(sf::Color::White);
		detector->show(window);

		for (auto& entity : entities) {
			entity->getShape()->update(1.f / 60);
			detector->updateEntity(entity);
			entity->getShape()->show(window);
		}

		window.display();
	}

	return 0;
}