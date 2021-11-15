#pragma once

#include "Shape.h"
#include "Entity.h"
#include <memory>

class CollisionDetector
{
public:
	virtual std::shared_ptr<Entity> addEntity(std::unique_ptr<Shape>& s) = 0;
	virtual bool updateEntity(const std::shared_ptr<Entity>& s) = 0;
	virtual std::vector<std::shared_ptr<Entity>> detectCollision(const std::shared_ptr<Entity>& s) = 0;
	virtual bool removeEntity(const std::shared_ptr<Entity>& s) = 0;
	virtual void show(sf::RenderWindow& rw) = 0;
};

