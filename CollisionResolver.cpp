#include "CollisionResolver.h"

bool CollisionResolver::handleCollision(const std::vector<std::shared_ptr<Entity>>& potentialCollisions)
{
	if (potentialCollisions.size() <= 1) return false;

	// split vector in pairs
	// check collisions
	// apply repulsion forces

}
