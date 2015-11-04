#pragma once
#include "EntityComponentSystem\AccessabilityMap.h"
#include "ResourceManagers.h"
#include "EntityComponentSystem\World.hpp"
#include <string>
namespace EntityComponentSystem {

	struct LevelManager
	{
		LevelManager();
    LevelManager(const std::string& filename, World& w);

    void loadLevel(const std::string& filename, World& w);


		~LevelManager();
  private:
    AccessabilityMap accessMap;
    ResourceManagers resourceManagers;
	};

};

