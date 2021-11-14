#include "Shape.h"

const sf::FloatRect& Shape::getBounds()
{
	return this->shape_->getGlobalBounds();
}

const sf::Vector2f& Shape::getPosition()
{
	return this->shape_->getPosition();
}

void Shape::applyForce(sf::Vector2f f)
{
	this->acceletarion_ += f;
}

void Shape::update(sf::Time dt)
{
	// @TODO - Decrease acceleration aka add air resistance or related

	this->velocity_ += this->acceletarion_ * dt.asSeconds();
	this->shape_->move(this->velocity_ * dt.asSeconds());

}
