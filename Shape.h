#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

class Shape
{
public:
	virtual ~Shape() = default;

	sf::FloatRect getBounds();
	const sf::Vector2f& getPosition();
	virtual void applyForce(sf::Vector2f f);
	virtual void update(sf::Time dt);
	virtual void show(sf::RenderWindow& rw) = 0;

protected:
	std::unique_ptr<sf::Shape> shape_;
	sf::Vector2f velocity_ = { 0,0 };
	sf::Vector2f acceletarion_ = { 0,0 };

};

