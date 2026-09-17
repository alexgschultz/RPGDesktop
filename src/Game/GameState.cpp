#include "rpg/Game/GameState.hpp"

GameState::GameState(const std::string& nomePlayer) : player(nomePlayer) {}

Player& GameState::getPlayer()
{
    return player;
}

const Player& GameState::getPlayer() const
{
    return player;
}

World& GameState::getWorld()
{
    return world;
}

const World& GameState::getWorld() const
{
    return world;
}

int GameState::getVidas() const
{
    return vidas;
}

bool GameState::perderVida()
{
    if (vidas <= 0) {
        return false;
    }

    vidas--;

    return vidas > 0;
}

[[nodiscard]] bool GameState::estaGameOver() const {
    return vidas <= 0;
}