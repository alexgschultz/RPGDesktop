#pragma once
#include "rpg/Character/Character.hpp"

class Combat
{
public:
    int atacar(const Character& atacante, Character& alvo) const;
};