#pragma once
#include <string>

enum class ItemType
{
    Cura,
    Mana
};

class Item
{
private:
    std::string name;
    ItemType type;

public:
    Item(const std::string& name, ItemType type);

    const std::string& getName() const;
    ItemType getType() const;
};