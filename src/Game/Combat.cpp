#include "rpg/Game/Combat.hpp"

#include <random>

int Combat::atacar(const Character& atacante, Character& alvo) const
{
    if (!atacante.estaVivo() || !alvo.estaVivo()) {
        return 0;
    }

    static std::mt19937 gerador(std::random_device{}());

    std::uniform_int_distribution<int> distribuicao(
        atacante.getAtaqueMinimo(),
        atacante.getAtaqueMaximo()
    );

    int dano = distribuicao(gerador);

    alvo.receberDano(dano);

    return dano;
}