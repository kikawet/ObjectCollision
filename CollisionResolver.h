#pragma once

#include <vector>
#include "Entity.h"

class CollisionResolver
{

	bool handleCollision(const std::vector<std::shared_ptr<Entity>>& potentialCollisions);

};

