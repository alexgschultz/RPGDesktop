#pragma once
#include "rpg/Character/Character.hpp"

class Monster : public Character {
public:
	Monster(const std::string& nome, int ataqueMinimo, int ataqueMaximo);
};