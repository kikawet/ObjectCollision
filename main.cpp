#include <iostream>
#include <memory>
#include "SpatialHash.h"
#include "SimulationHandler.h"

sf::IntRect WINDOW(
	{ 0,0 }, //Position
	{ 1080, 720 } //Size
);

int main()
{
	//Setup framerate clock
	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time updatesPerSecond = sf::seconds(1.f / 60.f);

	//Setup Scene
	sf::RenderWindow window(sf::VideoMode(WINDOW.width, WINDOW.height), "Circle Collision");
	SimulationHandler sh(window,
		std::make_unique<SpatialHash>(
			sf::Vector2f((float)WINDOW.left, (float)WINDOW.top),
			sf::Vector2f((float)WINDOW.left + WINDOW.width, (float)WINDOW.top + WINDOW.height),
			sf::Vector2i(50, 50) //must divide the size
		)
	);

	// Reset clock
	clock.restart();

	//Main loop
	while (window.isOpen())
	{
		sh.processEvents();		

		while (accumulator > updatesPerSecond) {
			accumulator -= updatesPerSecond;

			sh.update(clock.getElapsedTime());
		}

		sh.render();
		accumulator += clock.restart();
	}

	return 0;
}