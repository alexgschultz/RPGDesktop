#include "rpg/Game/Game.hpp"

Game::Game(const std::string& nomePlayer, int larguraMapa, int alturaMapa) : player(nomePlayer), map(larguraMapa, alturaMapa) {}

bool Game::moverPlayer(const Position& destino)
{
    if (!map.posicaoValida(destino)) {
        return false;
    }

    player.moverPara(destino);
    return true;
}

const Player& Game::getPlayer() const
{
    return player;
}

int Game::atacarMonster(Monster& monster)
{
    return combat.atacar(player, monster);
}

int Game::atacarPlayer(const Monster& monster)
{
    return combat.atacar(monster, player);
}