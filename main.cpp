#include <SFML/Graphics.hpp>
#include <iostream>
#include "Shape.h"
#include <vector>
#include "Ball.h"
#include <memory>
#include "CollisionDetector.h"
#include "SpatialHash.h"
#include "SimulationHandler.h"

sf::IntRect WINDOW(
	{ 0,0 }, //Position
	{ 1080, 720 } //Size
);

int main()
{
	//Setup framerate clock
	sf::Clock clock, elapsedTime;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time updatesPerSecond = sf::seconds(1.f / 60.f);

	//Setup Scene
	sf::RenderWindow window(sf::VideoMode(WINDOW.width, WINDOW.height), "Circle Collision");
	SimulationHandler sh(window,
		std::make_unique<SpatialHash>(
			sf::Vector2f(WINDOW.left, WINDOW.top),
			sf::Vector2f(WINDOW.left + WINDOW.width, WINDOW.top + WINDOW.height),
			sf::Vector2i(50, 50) //must divide the size
			)
	);

	// Reset clock
	elapsedTime.restart();

	//Main loop
	while (window.isOpen())
	{
		sh.processEvents();		

		while (accumulator > updatesPerSecond) {
			accumulator -= updatesPerSecond;

			sh.update(elapsedTime.restart());
		}

		sh.render();
		accumulator += clock.restart();
	}

	return 0;
}