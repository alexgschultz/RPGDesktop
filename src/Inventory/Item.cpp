#include "rpg/Inventory/Item.hpp"

Item::Item(const std::string& name, ItemType type) : name(name), type(type) {}

const std::string& Item::getName() const
{
    return name;
}

ItemType Item::getType() const
{
    return type;
}