#pragma once

#include <SFML/Graphics.hpp>
#include "CollisionDetector.h"

class SimulationHandler
{
public:
	SimulationHandler(sf::RenderWindow& rw, std::unique_ptr<CollisionDetector>&& cd);

	void processEvents();
	void update(sf::Time dt);
	void render();

private:
	sf::RenderWindow* rw_;
	std::vector<std::shared_ptr<Entity>> entities_;
	std::unique_ptr<CollisionDetector> collisionDetector_;
};

