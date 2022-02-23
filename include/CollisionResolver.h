#pragma once

#include <vector>
#include "Entity.h"

class CollisionResolver
{
public:
	bool handleCollision(const std::vector<std::shared_ptr<Entity>>& potentialCollisions);

private:
	
};

