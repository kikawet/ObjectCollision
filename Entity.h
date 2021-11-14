#pragma once

#include <memory>
#include <SFML/System/Vector2.hpp>
#include "Shape.h"

class Entity
{
public:
	const sf::FloatRect& getBounds();
	const sf::Vector2f& getPosition();
	const std::shared_ptr<Shape>& getShape();
	virtual ~Entity();

protected:
	std::shared_ptr<Shape> entity_;
};

