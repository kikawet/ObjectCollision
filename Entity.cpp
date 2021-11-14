#include "Entity.h"

const sf::FloatRect& Entity::getBounds()
{
	return this->entity_->getBounds();
}

const sf::Vector2f& Entity::getPosition()
{
	return this->entity_->getPosition();
}

const std::shared_ptr<Shape>& Entity::getShape()
{
	return this->entity_;
}

Entity::~Entity()
{
}
