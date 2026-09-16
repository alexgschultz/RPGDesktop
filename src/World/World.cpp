#include "rpg/World/World.hpp"
#include <stdexcept>

World::World() : village(RegionType::Village, 10, 8), forest(RegionType::Forest, 20, 15), cave(RegionType::Cave, 12, 10) {}

RegionType World::getCurrentRegionType() const
{
    return currentRegion;
}

void World::changeRegion(RegionType region) {
    currentRegion = region;
}

const Region& World::getCurrentRegion() const {
    switch (currentRegion) {
        case RegionType::Village:
            return village;
        case RegionType::Forest:
            return forest;
        case RegionType::Cave:
            return cave;
        default:
            throw std::logic_error("Invalid current region");
    }
}

bool World::advanceRegion() {
    switch (currentRegion) {
        case RegionType::Village:
            currentRegion = RegionType::Forest;
            return true;

        case RegionType::Forest:
            currentRegion = RegionType::Cave;
            return true;

        case RegionType::Cave:
            return false;
    }
    return false;
}