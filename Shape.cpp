#include "Shape.h"

sf::FloatRect Shape::getBounds()
{
	return std::move(this->shape_->getGlobalBounds());
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
	const float dumping = 0.7f;

	this->velocity_ += this->acceletarion_ * dt.asSeconds() * dumping;
	this->shape_->move(this->velocity_ * dt.asSeconds());
}
