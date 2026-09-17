#pragma once
#include "rpg/Character/Player.hpp"
#include "rpg/World/World.hpp"
#include <string>

class GameState
{
private:
    Player player;
    World world;
    int vidas{ 3 };

public:
    GameState(const std::string& nomePlayer);

    Player& getPlayer();
    const Player& getPlayer() const;

    World& getWorld();
    const World& getWorld() const;

    int getVidas() const;
    bool perderVida();
    [[nodiscard]] bool estaGameOver() const;
};