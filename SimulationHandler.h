#pragma once

#include <SFML/Graphics.hpp>
#include "CollisionDetector.h"
#include <random>

class SimulationHandler
{
public:
	SimulationHandler(sf::RenderWindow& rw, std::unique_ptr<CollisionDetector>&& cd);

	void processEvents();
	void update(sf::Time dt);
	void render();

private:
	double getRandom();

	sf::RenderWindow* rw_;
	std::vector<std::shared_ptr<Entity>> entities_;
	std::unique_ptr<CollisionDetector> collisionDetector_;
	std::mt19937_64 randomGen_;
	std::uniform_real_distribution<> random_;
};

