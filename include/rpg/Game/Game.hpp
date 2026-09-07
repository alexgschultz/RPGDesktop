#pragma once
#include "rpg/Character/Player.hpp"
#include "rpg/World/Map.hpp"
#include "rpg/World/Position.hpp"
#include "rpg/Character/Monster.hpp"
#include "rpg/Game/Combat.hpp"
#include <string>

class Game
{
private:
    Player player;
    Map map;
    Combat combat;

public:
    Game(const std::string& nomePlayer, int larguraMapa, int alturaMapa);
    bool moverPlayer(const Position& destino);
    const Player& getPlayer() const;
    int atacarMonster(Monster& monster);
    int atacarPlayer(const Monster& monster);
};