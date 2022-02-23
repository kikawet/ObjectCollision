#pragma once
#include "Entity.h"

class Utils
{
public:
	static std::vector<std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>>> combineEntities(const std::vector<std::shared_ptr<Entity>>& entities);

};

