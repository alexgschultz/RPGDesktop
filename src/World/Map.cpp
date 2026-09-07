#include "rpg/World/Map.hpp"

Map::Map(int largura, int altura) : largura(largura), altura(altura) {}

int Map::getLargura() const {
    return largura;
}

int Map::getAltura() const {
    return altura;
}

bool Map::posicaoValida(const Position& posicao) const
{
    return posicao.x >= 0 && posicao.x < largura && posicao.y >= 0 && posicao.y < altura;
}