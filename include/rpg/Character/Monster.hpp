#pragma once

#include "rpg/Character/Character.hpp"

class Monster : public Character
{
private:
    int experienciaRecompensa;

public:
    Monster(const std::string& nome, int ataqueMinimo, int ataqueMaximo, int experienciaRecompensa);

    int getExperienciaRecompensa() const;
};