#include "rpg/Character/Character.hpp"
#include "rpg/Character/Player.hpp"
#include "rpg/Character/Monster.hpp"
#include "rpg/World/Map.hpp"
#include "rpg/Game/Game.hpp"
#include "rpg/Game/Combat.hpp"
#include <iostream>
#include <string>

void check(int result, int expected, const std::string& testName);

int main()
{   
    std::cout << '\n';

    Game game("Player", 10, 8);

    check(game.getPlayer().getName() == "Player", true, "Game::nome do player");

    check(game.moverPlayer({ 4, 6 }), true, "Game::movimento valido");
    check(game.getPlayer().getPosicao().x, 4, "Game::player posicao x");
    check(game.getPlayer().getPosicao().y, 6, "Game::player posicao y");

    check(game.moverPlayer({ 10, 8 }), false, "Game::movimento invalido");
    check(game.getPlayer().getPosicao().x, 4, "Game::movimento invalido mantem x");
    check(game.getPlayer().getPosicao().y, 6, "Game::movimento invalido mantem y");

	std::cout << '\n';

    Character aliveCharacter("Alive");

    check(aliveCharacter.estaVivo(), true, "Character::estaVivo inicial");

    aliveCharacter.receberDano(99);
    check(aliveCharacter.estaVivo(), true, "Character::estaVivo com 1 de vida");

    aliveCharacter.receberDano(1);
    check(aliveCharacter.estaVivo(), false, "Character::estaVivo com 0 de vida");

    std::cout << '\n';

    Character attacker("Attacker", 5, 15);

    check(attacker.getAtaqueMinimo(), 5, "Character::ataque minimo inicial");
    check(attacker.getAtaqueMaximo(), 15, "Character::ataque maximo inicial");

    std::cout << '\n';

    Player player("Player");

    Combat combat;

    Player combatPlayer("Player");
    Monster combatMonster("Goblin", 10, 20);

    check(combatPlayer.getVida(), 100, "Combat::player vida inicial");
    check(combatMonster.getVida(), 100, "Combat::monster vida inicial");

    int danoPlayer = combat.atacar(combatPlayer, combatMonster);

    check(danoPlayer, 10, "Combat::dano player");
    check(combatMonster.getVida(), 90, "Combat::monster recebe dano");

    int danoMonster = combat.atacar(combatMonster, combatPlayer);

    check(danoMonster, 10, "Combat::dano monster");
    check(combatPlayer.getVida(), 90, "Combat::player recebe dano");

    combatMonster.receberDano(100);

    check(combatMonster.estaVivo(), false, "Combat::monster morto");
    check(combat.atacar(combatMonster, combatPlayer), 0, "Combat::morto nao ataca");

    std::cout << '\n';

    Player xpPlayer("Player");

    xpPlayer.ganharExperiencia(50);
    check(xpPlayer.getExperiencia(), 50, "Player::ganha 50 XP");

    xpPlayer.ganharExperiencia(30);
    check(xpPlayer.getExperiencia(), 80, "Player::acumula XP");

    xpPlayer.ganharExperiencia(-20);
    check(xpPlayer.getExperiencia(), 80, "Player::ignora XP negativo");

    std::cout << '\n';

    check(player.getName() == "Player", true, "Player::nome");
    check(player.getLevel(), 1, "Player::level inicial");
    check(player.getExperiencia(), 0, "Player::experiencia inicial");

    check(player.getVida(), 100, "Player::vida herdada");

    player.receberDano(25);
    check(player.getVida(), 75, "Player::receberDano herdado");

	std::cout << '\n';

    Monster monster("Monster", 10, 20);

	check(monster.getName() == "Monster", true, "Monster::nome");
    check(monster.getVida(), 100, "Monster::vida inicial");

    monster.receberDano(40);
    check(monster.getVida(), 60, "Monster::receberDano herdado");

    check(danoMonster >= 10 && danoMonster <= 20, true, "Combat::dano monster na faixa");
    check(combatPlayer.getVida(), 100 - danoMonster, "Combat::player recebe dano");

    std::cout << '\n';

    Monster goblin("Goblin", 5, 10);
    Monster ogre("Ogre", 10, 20);
    Monster dragon("Dragon", 20, 35);

    check(goblin.getAtaqueMinimo(), 5, "Goblin::ataque minimo");
    check(goblin.getAtaqueMaximo(), 10, "Goblin::ataque maximo");

    check(ogre.getAtaqueMinimo(), 10, "Ogre::ataque minimo");
    check(ogre.getAtaqueMaximo(), 20, "Ogre::ataque maximo");

    check(dragon.getAtaqueMinimo(), 20, "Dragon::ataque minimo");
    check(dragon.getAtaqueMaximo(), 35, "Dragon::ataque maximo");

    std::cout << '\n';

    Game combatGame("Player", 10, 8);
    Monster gameGoblin("Goblin", 5, 10);

    int dano = combatGame.atacarMonster(gameGoblin);

    check(dano, 10, "Game::player causa dano");
    check(gameGoblin.getVida(), 90, "Game::monster recebe dano");

    std::cout << '\n';

    Game combatGame2("Player", 10, 8);
    Monster attackingGoblin("Goblin", 5, 10);

    int danoGoblin = combatGame2.atacarPlayer(attackingGoblin);

    check(danoGoblin >= 5 && danoGoblin <= 10, true, "Game::monster dano na faixa");
    check(combatGame2.getPlayer().getVida(), 100 - danoGoblin, "Game::player recebe dano");

    std::cout << '\n';

    Character character("Character");

    check(character.getName() == "Character", true, "Character::nome");
    check(character.getVida(), 100, "Character::vida inicial");

    character.receberDano(20);
    check(character.getVida(), 80, "Character::receberDano 20");

    std::cout << '\n';

    Map map(10, 8);

    check(map.posicaoValida({ 0, 0 }), true, "Map::posicao inicial valida");
    check(map.posicaoValida({ 9, 7 }), true, "Map::posicao limite valida");
    check(map.posicaoValida({ -1, 0 }), false, "Map::x negativo");
    check(map.posicaoValida({ 0, -1 }), false, "Map::y negativo");
    check(map.posicaoValida({ 10, 0 }), false, "Map::x fora do limite");
    check(map.posicaoValida({ 0, 8 }), false, "Map::y fora do limite");

    std::cout << '\n';

    character.moverPara({ 3, 5 });

    check(character.getPosicao().x, 3, "Character::posicao x");
    check(character.getPosicao().y, 5, "Character::posicao y");

    character.moverPara({ 8, 2 });

    check(character.getPosicao().x, 8, "Character::nova posicao x");
    check(character.getPosicao().y, 2, "Character::nova posicao y");

    std::cout << '\n';

    character.receberDano(20);
    check(character.getVida(), 60, "Character::receberDano 20 novamente");

    character.receberDano(50);
    check(character.getVida(), 10, "Character::receberDano 50");

    character.receberDano(50);
    check(character.getVida(), 0, "Character::vida minima");

    character.receberDano(0);
    check(character.getVida(), 0, "Character::dano zero");

    character.receberDano(-10);
    check(character.getVida(), 0, "Character::dano negativo");

    std::cout << '\n';

    character.recuperarVida(30);
    check(character.getVida(), 30, "Character::recuperarVida 30");

    character.recuperarVida(50);
    check(character.getVida(), 80, "Character::recuperarVida 50");

    character.recuperarVida(50);
    check(character.getVida(), 100, "Character::vida maxima");

    character.recuperarVida(0);
    check(character.getVida(), 100, "Character::recuperarVida zero");

    character.recuperarVida(-20);
    check(character.getVida(), 100, "Character::recuperarVida negativa");

    std::cout << '\n';

    character.gastarMana(30);
    check(character.getMana(), 70, "Character::gastarMana 30");

    character.gastarMana(100);
    check(character.getMana(), 0, "Character::mana minima");

    character.gastarMana(-10);
    check(character.getMana(), 0, "Character::gastarMana negativa");

    std::cout << '\n';

    character.recuperarMana(40);
    check(character.getMana(), 40, "Character::recuperarMana 40");

    character.recuperarMana(100);
    check(character.getMana(), 100, "Character::mana maxima");

    character.recuperarMana(-20);
    check(character.getMana(), 100, "Character::recuperarMana negativa");

    return 0;
}

void check(int result, int expected, const std::string& testName)
{
    if (result == expected) {
        std::cout << "[PASS] " << testName << '\n';
    }
    else {
        std::cout << "[FAIL] " << testName << '\n';
    }
}