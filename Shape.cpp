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

void Shape::update(float dt)
{
	// @TODO - Decrease acceleration aka add air resistance or related

	this->velocity_ += this->acceletarion_ * dt;
	this->shape_->move(this->velocity_ * dt);

	this->acceletarion_ = { 0,0 };
}
