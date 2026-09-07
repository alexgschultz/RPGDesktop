#pragma once
#include "rpg/Character/Character.hpp"

class Player : public Character
{
private:
    int level{ 1 };
    int experiencia{ 0 };

public:
    int getLevel() const;
    int getExperiencia() const;
    void ganharExperiencia(int quantidade);
    Player(const std::string& nome);
};