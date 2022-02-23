#include "Ball.h"

Ball::Ball(sf::Vector2f position, float radius, sf::Color fillColor)
{
	shape_ = std::make_unique<sf::CircleShape>(radius);
	shape_->setPosition(position);
	shape_->setOutlineColor(fillColor);
	shape_->setOutlineThickness(2.f);
	shape_->setFillColor(sf::Color::Transparent);


}

void Ball::show(sf::RenderWindow& rw)
{
	rw.draw(*shape_);
}
