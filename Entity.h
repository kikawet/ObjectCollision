#pragma once

#include <SFML/System/Vector2.hpp>
#include "Shape.h"

class Entity
{
public:
	sf::FloatRect getBounds();
	const sf::Vector2f& getPosition();
	const std::unique_ptr<Shape>& getShape();
	virtual ~Entity();

protected:
	std::unique_ptr<Shape> entity_;
};

