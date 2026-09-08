#include "rpg/Character/Monster.hpp"

Monster::Monster(const std::string& nome, int ataqueMinimo, int ataqueMaximo, int experienciaRecompensa)
    : Character(nome, ataqueMinimo, ataqueMaximo), experienciaRecompensa(experienciaRecompensa) {}

int Monster::getExperienciaRecompensa() const
{
    return experienciaRecompensa;
}