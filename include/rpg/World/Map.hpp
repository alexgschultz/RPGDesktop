#pragma once
#include "rpg/World/Position.hpp"

class Map {
private:
    int largura;
    int altura;

public:
    Map(int largura, int altura);

    int getLargura() const;
    int getAltura() const;

    bool posicaoValida(const Position& posicao) const;
};