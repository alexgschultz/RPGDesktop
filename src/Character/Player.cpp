#include "rpg/Character/Player.hpp"

Player::Player(const std::string& nome) : Character(nome, 10, 10) {}

int Player::getLevel() const
{
	return level;
}

int Player::getExperiencia() const
{
	return experiencia;
}

int Player::experienciaNecessaria() const {
	return level * 100;
}

void Player::ganharExperiencia(int quantidade) {
	if (quantidade < 0) {
		return;
	}
	experiencia += quantidade;

	while (experiencia >= experienciaNecessaria()) {
		experiencia -= experienciaNecessaria();
		level++;
	}
}