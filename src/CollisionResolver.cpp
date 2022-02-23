#include "CollisionResolver.h"
#include "Utils.h"

bool CollisionResolver::handleCollision(const std::vector<std::shared_ptr<Entity>>& potentialCollisions)
{
	if (potentialCollisions.size() <= 1) return false;

	// @DONE: split vector in pairs
	const auto pairs = Utils::combineEntities(potentialCollisions);

	// @TODO: implement collision
	// 1) check if pair is actually colliding -> collision_detector.areColliding
	// 2) calculate forces
	// 3) apply forces
	

	// @TODO: apply repulsion forces

	return false;
}
