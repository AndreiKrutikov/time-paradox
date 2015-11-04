#pragma once
#include <EntityComponentSystem/System.hpp>
#include "../Components/Movable.h"
#include "../Components/Region.h"
#include <map>
namespace Engine {

	class RegionSystem : public EntityComponentSystem::System<RegionSystem> {
	public:
    RegionSystem();
    void update();

	private:
    bool isInRegion(EntityComponentSystem::Entity const &movableEntity, EntityComponentSystem::Entity const &regionEntity) const;
    int32_t findInMap(std::pair <uint64_t, uint64_t> p);
    std::vector <std:: pair <uint64_t, uint64_t> > movableToRegion;
	};

}
