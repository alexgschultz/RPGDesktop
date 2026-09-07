#include "rpg/Character/Player.hpp"

void Player::ganharExperiencia(int quantidade) {
	if (quantidade < 0) {
		return;
	}
	experiencia += quantidade;
}

int Player::getLevel() const 
{
	return level;
}

int Player::getExperiencia() const 
{
	return experiencia;
}

Player::Player(const std::string& nome) : Character(nome, 10, 10) {}