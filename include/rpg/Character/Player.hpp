#pragma once
#include "rpg/Character/Character.hpp"
#include "rpg/Inventory/Inventory.hpp"

class Player : public Character
{
private:
    int level{ 1 };
    int experiencia{ 0 };
    Inventory inventory;

public:
    int getLevel() const;
    int getExperiencia() const;
    void ganharExperiencia(int quantidade);
    int experienciaNecessaria() const;
    Player(const std::string& nome);
    Inventory& getInventory();
    const Inventory& getInventory() const;

    void restaurarProgressao(int level, int experiencia);
};