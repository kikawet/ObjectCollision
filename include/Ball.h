#pragma once
#include "Shape.h"

class Ball :
	public Shape
{
public:
	Ball(sf::Vector2f position, float radius = 100, sf::Color cofillColorlor = sf::Color::Magenta);
	virtual ~Ball() = default;

	void show(sf::RenderWindow& rw) override;

private:
};

