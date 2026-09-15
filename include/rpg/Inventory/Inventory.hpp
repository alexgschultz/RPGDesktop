#pragma once
#include "rpg/Inventory/Item.hpp"
#include "rpg/Character/Character.hpp"
#include <vector>

class Inventory
{
private:
    std::vector<Item> items;

public:
    void adicionar(const Item& item);
    int quantidade() const;
    bool remover(int indice);
    bool usar(int indice, Character& character);
};