#include "rpg/World/Region.hpp"

Region::Region(RegionType type, int largura, int altura) : type(type), map(largura, altura){}

RegionType Region::getType() const
{
    return type;
}

const Map& Region::getMap() const
{
    return map;
}