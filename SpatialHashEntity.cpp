#include "Entity.h"
#include "SpatialHashEntity.h"

SpatialHashEntity::SpatialHashEntity(std::shared_ptr<Shape>& s) :
	TLCell_(sf::Vector2i(-1,-1)),
	BRCell_(sf::Vector2i(-1, -1)),
	queryId_(-1),
	nodes_()
{
	entity_ = s;
}
