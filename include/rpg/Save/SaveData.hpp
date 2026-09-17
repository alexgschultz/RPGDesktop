#pragma once
#include "rpg/Inventory/Item.hpp"
#include "rpg/World/Region.hpp"
#include <string>
#include <vector>

struct SaveData
{
    std::string playerName;

    int vida{ 100 };
    int mana{ 100 };

    int level{ 1 };
    int experiencia{ 0 };

    int vidas{ 3 };

    RegionType region{ RegionType::Village };

    std::vector<Item> items;
};