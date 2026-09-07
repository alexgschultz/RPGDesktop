#include "rpg/Character/Character.hpp"

Character::Character(const std::string& nome, int ataqueMinimo, int ataqueMaximo) : name(nome), ataqueMinimo(ataqueMinimo), ataqueMaximo(ataqueMaximo) {}

std::string Character::getName() const
{
	return name;
}

int Character::getVida() const
{
	return vida;
}

int Character::getVidaMaxima() const
{
	return vidaMaxima;
}

int Character::getMana() const
{
	return mana;
}

int Character::getManaMaxima() const
{
	return manaMaxima;
}

Position Character::getPosicao() const
{
	return posicao;
}

void Character::receberDano(int dano)
{
	if (dano < 0) {
		return;
	}

	vida -= dano;

	if (vida < 0) {
		vida = 0;
	}
}

void Character::recuperarVida(int quantidade)
{
	if (quantidade < 0) {
		return;
	}

	vida += quantidade;

	if (vida > vidaMaxima) {
		vida = vidaMaxima;
	}
}

void Character::gastarMana(int quantidade)
{
	if (quantidade < 0) {
		return;
	}

	mana -= quantidade;

	if (mana < 0) {
		mana = 0;
	}
}

void Character::recuperarMana(int quantidade)
{
	if (quantidade < 0) {
		return;
	}

	mana += quantidade;

	if (mana > manaMaxima) {
		mana = manaMaxima;
	}
}

void Character::moverPara(const Position& novaPosicao)
{
	posicao = novaPosicao;
}

bool Character::estaVivo() const {
	return vida > 0;
}

int Character::getAtaqueMinimo() const
{
	return ataqueMinimo;
}

int Character::getAtaqueMaximo() const
{
	return ataqueMaximo;
}