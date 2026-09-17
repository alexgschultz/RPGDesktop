#include "rpg/Character/Player.hpp"
#include <algorithm>

Player::Player(const std::string& nome) : Character(nome, 10, 10) {}

Inventory& Player::getInventory()
{
	return inventory;
}

const Inventory& Player::getInventory() const
{
	return inventory;
}

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

void Player::restaurarProgressao(int level, int experiencia)
{
	this->level = std::max(1, level);
	this->experiencia = std::max(0, experiencia);
}