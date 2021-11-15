#pragma once

#include "CollisionDetector.h"
#include "SpatialHashEntity.h"

class SpatialHash :
	public CollisionDetector
{
public:
	SpatialHash(const sf::Vector2f& bMin, const sf::Vector2f& bMax, const sf::Vector2i& dimensions);
	virtual ~SpatialHash();

	std::shared_ptr<Entity> addEntity(std::unique_ptr<Shape>& s) override;
	bool updateEntity(const std::shared_ptr<Entity>& entity) override;
	std::vector<std::shared_ptr<Entity>> detectCollision(const std::shared_ptr<Entity>& entity) override;
	bool removeEntity(const std::shared_ptr<Entity>& entity) override;
	void show(sf::RenderWindow& rw);


private:
	sf::Vector2i getCellIndex(const sf::Vector2f& pos);
	bool insert(const std::shared_ptr<SpatialHashEntity>& entity);
	bool containsEntity(const std::shared_ptr<SpatialHashEntity>& entity);

	std::vector<std::shared_ptr<SpatialHashEntity::Node>> cells_;
	sf::Vector2i dimensions_;
	sf::Vector2f boundsMin_;
	sf::Vector2f boundsMax_;
	int queryIds_;
};

