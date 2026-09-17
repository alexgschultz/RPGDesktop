#pragma once
#include "rpg/World/Position.hpp"
#include <string>

class Character {
private:
	std::string name;
	int vida{100};
	int vidaMaxima{100};
	int mana{100};
	int manaMaxima{100};
	int ataqueMinimo{ 10 };
	int ataqueMaximo{ 10 };
	Position posicao;

public:
	void receberDano(int dano);
	void recuperarVida(int quantidade);
	void gastarMana(int quantidade);
	void recuperarMana(int quantidade);
	void moverPara(const Position& posicao);
	void restaurarEstado(int vida, int mana);
	bool estaVivo() const;
	int getAtaqueMinimo() const;
	int getAtaqueMaximo() const;

	int getVida() const;
	int getVidaMaxima() const;
	int getMana() const;
	int getManaMaxima() const;
	Position getPosicao() const;

	Character(const std::string& nome, int ataqueMinimo = 10, int ataqueMaximo = 10);

	std::string getName() const;
};