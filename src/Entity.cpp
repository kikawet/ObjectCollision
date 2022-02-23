#include "Entity.h"

sf::FloatRect Entity::getBounds()
{
	return std::move(this->entity_->getBounds());
}

const sf::Vector2f& Entity::getPosition()
{
	return this->entity_->getPosition();
}

const std::unique_ptr<Shape>& Entity::getShape()
{
	return this->entity_;
}

Entity::~Entity()
{
}
