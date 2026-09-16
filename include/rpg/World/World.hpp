#pragma once
#include "rpg/World/Region.hpp"

class World
{
private:
    Region village;
    Region forest;
    Region cave;

    RegionType currentRegion{ RegionType::Village };

public:
    World();

    RegionType getCurrentRegionType() const;
    const Region& getCurrentRegion() const;
    [[nodiscard]] bool advanceRegion();

    void changeRegion(RegionType region);
};