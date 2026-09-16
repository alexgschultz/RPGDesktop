#pragma once
#include "rpg/World/Map.hpp"

enum class RegionType
{
    Village,
    Forest,
    Cave
};

class Region
{
private:
    RegionType type;
    Map map;

public:
    Region(RegionType type, int largura, int altura);

    RegionType getType() const;
    const Map& getMap() const;
};