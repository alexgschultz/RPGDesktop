#include "rpg/Character/Character.hpp"
#include "rpg/Character/Player.hpp"
#include "rpg/Character/Monster.hpp"
#include "rpg/World/Map.hpp"
#include "rpg/Game/Game.hpp"
#include "rpg/Game/Combat.hpp"
#include "rpg/Inventory/Item.hpp"
#include "rpg/Inventory/Inventory.hpp"
#include "rpg/World/Region.hpp"
#include "rpg/World/World.hpp"
#include "rpg/Game/GameState.hpp"

#include <iostream>
#include <string>

void check(int result, int expected, const std::string& testName);

int main()
{
    // =========================================================
    // Game - movimento
    // =========================================================

    std::cout << "\n--- Game / Movimento ---\n";

    Game game("Player", 10, 8);

    check(game.getPlayer().getName() == "Player", true, "Game::nome do player");

    check(game.moverPlayer({ 4, 6 }), true, "Game::movimento valido");
    check(game.getPlayer().getPosicao().x, 4, "Game::player posicao x");
    check(game.getPlayer().getPosicao().y, 6, "Game::player posicao y");

    check(game.moverPlayer({ 10, 8 }), false, "Game::movimento invalido");
    check(game.getPlayer().getPosicao().x, 4, "Game::movimento invalido mantem x");
    check(game.getPlayer().getPosicao().y, 6, "Game::movimento invalido mantem y");

    // =========================================================
    // Game - recompensa de experiencia
    // =========================================================

    std::cout << "\n--- Game / Recompensa de Experiencia ---\n";

    Game xpGame("Player", 10, 8);
    Monster xpGameGoblin("Goblin", 5, 10, 50);

    xpGameGoblin.receberDano(90);

    check(xpGameGoblin.getVida(), 10, "Game::Goblin antes do golpe final");
    check(xpGame.getPlayer().getExperiencia(), 0, "Game::Player XP antes da vitoria");

    int danoFinal = xpGame.atacarMonster(xpGameGoblin);

    check(danoFinal, 10, "Game::golpe final");
    check(xpGameGoblin.estaVivo(), false, "Game::Goblin derrotado");
    check(xpGame.getPlayer().getExperiencia(), 50, "Game::Player recebe XP");

    xpGame.atacarMonster(xpGameGoblin);

    check(xpGame.getPlayer().getExperiencia(), 50, "Game::nao recebe XP duplicado");

    // =========================================================
    // Character - estaVivo
    // =========================================================

    std::cout << "\n--- Character / estaVivo ---\n";

    Character aliveCharacter("Alive");

    check(aliveCharacter.estaVivo(), true, "Character::estaVivo inicial");

    aliveCharacter.receberDano(99);
    check(aliveCharacter.estaVivo(), true, "Character::estaVivo com 1 de vida");

    aliveCharacter.receberDano(1);
    check(aliveCharacter.estaVivo(), false, "Character::estaVivo com 0 de vida");

    // =========================================================
    // Character - ataque
    // =========================================================

    std::cout << "\n--- Character / Ataque ---\n";

    Character attacker("Attacker", 5, 15);

    check(attacker.getAtaqueMinimo(), 5, "Character::ataque minimo");
    check(attacker.getAtaqueMaximo(), 15, "Character::ataque maximo");

    // =========================================================
    // Combat
    // =========================================================

    std::cout << "\n--- Combat ---\n";

    Combat combat;

    Player combatPlayer("Player");
    Monster combatMonster("Goblin", 10, 20, 50);

    check(combatPlayer.getVida(), 100, "Combat::player vida inicial");
    check(combatMonster.getVida(), 100, "Combat::monster vida inicial");

    int danoPlayer = combat.atacar(combatPlayer, combatMonster);

    check(danoPlayer, 10, "Combat::dano player");
    check(combatMonster.getVida(), 90, "Combat::monster recebe dano");

    int danoMonster = combat.atacar(combatMonster, combatPlayer);

    check(danoMonster >= 10 && danoMonster <= 20, true, "Combat::dano monster na faixa");
    check(combatPlayer.getVida(), 100 - danoMonster, "Combat::player recebe dano");

    combatMonster.receberDano(100);

    check(combatMonster.estaVivo(), false, "Combat::monster morto");
    check(combat.atacar(combatMonster, combatPlayer), 0, "Combat::morto nao ataca");

    // =========================================================
    // Player - experiencia e level
    // =========================================================

    std::cout << "\n--- Player / Experiencia ---\n";

    Player xpPlayer("Player");

    check(xpPlayer.getLevel(), 1, "Player::level inicial");
    check(xpPlayer.getExperiencia(), 0, "Player::experiencia inicial");
    check(xpPlayer.experienciaNecessaria(), 100, "Player::XP necessaria level 1");

    xpPlayer.ganharExperiencia(50);

    check(xpPlayer.getLevel(), 1, "Player::continua level 1");
    check(xpPlayer.getExperiencia(), 50, "Player::ganha 50 XP");

    xpPlayer.ganharExperiencia(50);

    check(xpPlayer.getLevel(), 2, "Player::sobe para level 2");
    check(xpPlayer.getExperiencia(), 0, "Player::XP apos level up");
    check(xpPlayer.experienciaNecessaria(), 200, "Player::XP necessaria level 2");

    xpPlayer.ganharExperiencia(30);

    check(xpPlayer.getExperiencia(), 30, "Player::acumula XP");

    xpPlayer.ganharExperiencia(-20);

    check(xpPlayer.getExperiencia(), 30, "Player::ignora XP negativo");

    // Teste de varios levels de uma vez
    Player multiLevelPlayer("Player");

    multiLevelPlayer.ganharExperiencia(350);

    check(multiLevelPlayer.getLevel(), 3, "Player::sobe varios levels");
    check(multiLevelPlayer.getExperiencia(), 50, "Player::mantem XP excedente");

    // =========================================================
    // Player - heranca
    // =========================================================

    std::cout << "\n--- Player / Heranca ---\n";

    Player player("Player");

    check(player.getName() == "Player", true, "Player::nome");
    check(player.getLevel(), 1, "Player::level inicial");
    check(player.getExperiencia(), 0, "Player::experiencia inicial");
    check(player.getVida(), 100, "Player::vida herdada");

    player.receberDano(25);

    check(player.getVida(), 75, "Player::receberDano herdado");

    // =========================================================
    // Monster
    // =========================================================

    std::cout << "\n--- Monster ---\n";

    Monster monster("Monster", 10, 20, 50);

    check(monster.getName() == "Monster", true, "Monster::nome");
    check(monster.getVida(), 100, "Monster::vida inicial");
    check(monster.getExperienciaRecompensa(), 50, "Monster::recompensa XP");

    monster.receberDano(40);

    check(monster.getVida(), 60, "Monster::receberDano herdado");

    // =========================================================
    // Goblin / Ogre / Dragon
    // =========================================================

    std::cout << "\n--- Monstros ---\n";

    Monster goblin("Goblin", 5, 10, 50);
    Monster ogre("Ogre", 10, 20, 100);
    Monster dragon("Dragon", 20, 35, 200);

    check(goblin.getAtaqueMinimo(), 5, "Goblin::ataque minimo");
    check(goblin.getAtaqueMaximo(), 10, "Goblin::ataque maximo");
    check(goblin.getExperienciaRecompensa(), 50, "Goblin::recompensa XP");

    check(ogre.getAtaqueMinimo(), 10, "Ogre::ataque minimo");
    check(ogre.getAtaqueMaximo(), 20, "Ogre::ataque maximo");
    check(ogre.getExperienciaRecompensa(), 100, "Ogre::recompensa XP");

    check(dragon.getAtaqueMinimo(), 20, "Dragon::ataque minimo");
    check(dragon.getAtaqueMaximo(), 35, "Dragon::ataque maximo");
    check(dragon.getExperienciaRecompensa(), 200, "Dragon::recompensa XP");

    // =========================================================
    // Item
    // =========================================================

    std::cout << "\n--- Item ---\n";

    Item pocaoCura("Pocao de Cura", ItemType::Cura);
    Item pocaoMana("Pocao de Mana", ItemType::Mana);

    check(pocaoCura.getName() == "Pocao de Cura", true, "Item::nome cura");
    check(pocaoCura.getType() == ItemType::Cura, true, "Item::tipo cura");

    check(pocaoMana.getName() == "Pocao de Mana", true, "Item::nome mana");
    check(pocaoMana.getType() == ItemType::Mana, true, "Item::tipo mana");

    // =========================================================
    // Inventory
    // =========================================================

    std::cout << "\n--- Inventory ---\n";

    Inventory inventory;

    check(inventory.quantidade(), 0, "Inventory::quantidade inicial");

    inventory.adicionar(pocaoCura);
    check(inventory.quantidade(), 1, "Inventory::adiciona item");

    inventory.adicionar(pocaoMana);
    check(inventory.quantidade(), 2, "Inventory::adiciona segundo item");

    check(inventory.remover(0), true, "Inventory::remove primeiro item");
    check(inventory.quantidade(), 1, "Inventory::quantidade apos remover");

    check(inventory.remover(10), false, "Inventory::indice invalido");
    check(inventory.quantidade(), 1, "Inventory::quantidade mantida");

    check(inventory.remover(-1), false, "Inventory::indice negativo");

    std::cout << "\n--- Inventory / Usar Item ---\n";

    Inventory useInventory;

    Item cura("Pocao de Cura", ItemType::Cura);
    Item mana("Pocao de Mana", ItemType::Mana);

    useInventory.adicionar(cura);
    useInventory.adicionar(mana);

    Character itemCharacter("Character");

    itemCharacter.receberDano(80);
    check(itemCharacter.getVida(), 20, "Inventory::vida antes da cura");

    check(useInventory.usar(0, itemCharacter), true, "Inventory::usa item de cura");
    check(itemCharacter.getVida(), 70, "Inventory::cura 50 porcento");
    check(useInventory.quantidade(), 1, "Inventory::remove item usado");

    itemCharacter.gastarMana(80);
    check(itemCharacter.getMana(), 20, "Inventory::mana antes da recuperacao");

    check(useInventory.usar(0, itemCharacter), true, "Inventory::usa item de mana");
    check(itemCharacter.getMana(), 70, "Inventory::recupera 50 porcento mana");
    check(useInventory.quantidade(), 0, "Inventory::remove item de mana");

    check(useInventory.usar(0, itemCharacter), false, "Inventory::nao usa indice invalido");

    // =========================================================
    // Player - Inventory
    // =========================================================

    std::cout << "\n--- Player / Inventory ---\n";

    Player inventoryPlayer("Player");

    inventoryPlayer.getInventory().adicionar(pocaoCura);

    check(inventoryPlayer.getInventory().quantidade(), 1, "Player::possui item no inventario");

    inventoryPlayer.receberDano(80);

    check(inventoryPlayer.getVida(), 20, "Player::vida antes de usar cura");

    check(inventoryPlayer.getInventory().usar(0, inventoryPlayer), true, "Player::usa item de cura");

    check(inventoryPlayer.getVida(), 70, "Player::vida apos usar cura");
    check(inventoryPlayer.getInventory().quantidade(), 0, "Player::inventario remove item usado");

    // =========================================================
    // Game - combate
    // =========================================================

    std::cout << "\n--- Game / Combate ---\n";

    Game combatGame("Player", 10, 8);
    Monster gameGoblin("Goblin", 5, 10, 50);

    int danoGamePlayer = combatGame.atacarMonster(gameGoblin);

    check(danoGamePlayer, 10, "Game::player causa dano");
    check(gameGoblin.getVida(), 90, "Game::monster recebe dano");

    Game combatGame2("Player", 10, 8);
    Monster attackingGoblin("Goblin", 5, 10, 50);

    int danoGoblin = combatGame2.atacarPlayer(attackingGoblin);

    check(danoGoblin >= 5 && danoGoblin <= 10, true, "Game::monster dano na faixa");
    check(combatGame2.getPlayer().getVida(), 100 - danoGoblin, "Game::player recebe dano");

    // =========================================================
    // Character - estado inicial e dano
    // =========================================================

    std::cout << "\n--- Character / Vida ---\n";

    Character character("Character");

    check(character.getName() == "Character", true, "Character::nome");
    check(character.getVida(), 100, "Character::vida inicial");
    check(character.getVidaMaxima(), 100, "Character::vida maxima inicial");

    character.receberDano(20);
    check(character.getVida(), 80, "Character::receberDano 20");

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

    // =========================================================
    // Character - recuperar vida
    // =========================================================

    std::cout << "\n--- Character / Recuperar Vida ---\n";

    character.recuperarVida(30);
    check(character.getVida(), 30, "Character::recuperarVida 30");

    character.recuperarVida(50);
    check(character.getVida(), 80, "Character::recuperarVida 50");

    character.recuperarVida(50);
    check(character.getVida(), 100, "Character::limite vida maxima");

    character.recuperarVida(0);
    check(character.getVida(), 100, "Character::recuperarVida zero");

    character.recuperarVida(-20);
    check(character.getVida(), 100, "Character::recuperarVida negativa");

    // =========================================================
    // Character - mana
    // =========================================================

    std::cout << "\n--- Character / Mana ---\n";

    check(character.getMana(), 100, "Character::mana inicial");
    check(character.getManaMaxima(), 100, "Character::mana maxima inicial");

    character.gastarMana(30);
    check(character.getMana(), 70, "Character::gastarMana 30");

    character.gastarMana(100);
    check(character.getMana(), 0, "Character::mana minima");

    character.gastarMana(-10);
    check(character.getMana(), 0, "Character::gastarMana negativa");

    character.recuperarMana(40);
    check(character.getMana(), 40, "Character::recuperarMana 40");

    character.recuperarMana(100);
    check(character.getMana(), 100, "Character::mana maxima");

    character.recuperarMana(-20);
    check(character.getMana(), 100, "Character::recuperarMana negativa");

    // =========================================================
    // Map
    // =========================================================

    std::cout << "\n--- Map ---\n";

    Map map(10, 8);

    check(map.getLargura(), 10, "Map::largura");
    check(map.getAltura(), 8, "Map::altura");

    check(map.posicaoValida({ 0, 0 }), true, "Map::posicao inicial valida");
    check(map.posicaoValida({ 9, 7 }), true, "Map::posicao limite valida");

    check(map.posicaoValida({ -1, 0 }), false, "Map::x negativo");
    check(map.posicaoValida({ 0, -1 }), false, "Map::y negativo");

    check(map.posicaoValida({ 10, 0 }), false, "Map::x fora do limite");
    check(map.posicaoValida({ 0, 8 }), false, "Map::y fora do limite");

    // =========================================================
    // Region
    // =========================================================

    std::cout << "\n--- Region ---\n";

    Region village(RegionType::Village, 10, 8);
    Region forest(RegionType::Forest, 20, 15);
    Region cave(RegionType::Cave, 12, 10);

    check(village.getType() == RegionType::Village, true, "Region::Village tipo");
    check(forest.getType() == RegionType::Forest, true, "Region::Forest tipo");
    check(cave.getType() == RegionType::Cave, true, "Region::Cave tipo");

    check(village.getMap().getLargura(), 10, "Region::Village largura");
    check(village.getMap().getAltura(), 8, "Region::Village altura");

    check(forest.getMap().getLargura(), 20, "Region::Forest largura");
    check(cave.getMap().getAltura(), 10, "Region::Cave altura");

    // =========================================================
    // World
    // =========================================================

    std::cout << "\n--- World ---\n";

    World world;

    check(world.getCurrentRegionType() == RegionType::Village, true, "World::regiao inicial Village");

    check(world.getCurrentRegion().getType() == RegionType::Village, true, "World::retorna Village");
    check(world.getCurrentRegion().getMap().getLargura(), 10, "World::Village largura");
    check(world.getCurrentRegion().getMap().getAltura(), 8, "World::Village altura");

    world.changeRegion(RegionType::Forest);

    check(world.getCurrentRegionType() == RegionType::Forest, true, "World::muda para Forest");
    check(world.getCurrentRegion().getMap().getLargura(), 20, "World::Forest largura");
    check(world.getCurrentRegion().getMap().getAltura(), 15, "World::Forest altura");

    world.changeRegion(RegionType::Cave);

    check(world.getCurrentRegionType() == RegionType::Cave, true, "World::muda para Cave");
    check(world.getCurrentRegion().getMap().getLargura(), 12, "World::Cave largura");
    check(world.getCurrentRegion().getMap().getAltura(), 10, "World::Cave altura");

    World progressionWorld;

    check(progressionWorld.getCurrentRegionType() == RegionType::Village, true, "World::progressao inicia Village");

    check(progressionWorld.advanceRegion(), true, "World::avanca para Forest");
    check(progressionWorld.getCurrentRegionType() == RegionType::Forest, true, "World::regiao Forest");

    check(progressionWorld.advanceRegion(), true, "World::avanca para Cave");
    check(progressionWorld.getCurrentRegionType() == RegionType::Cave, true, "World::regiao Cave");

    check(progressionWorld.advanceRegion(), false, "World::Cave nao possui proxima regiao");
    check(progressionWorld.getCurrentRegionType() == RegionType::Cave, true, "World::permanece na Cave");

    // =========================================================
    // GameState
    // =========================================================

    std::cout << "\n--- GameState ---\n";

    GameState gameState("Player");

    check(gameState.getVidas(), 3, "GameState::vidas iniciais");

    check(gameState.perderVida(), true, "GameState::perde primeira vida");
    check(gameState.getVidas(), 2, "GameState::restam 2 vidas");

    check(gameState.perderVida(), true, "GameState::perde segunda vida");
    check(gameState.getVidas(), 1, "GameState::resta 1 vida");

    check(gameState.perderVida(), false, "GameState::perde ultima vida");
    check(gameState.getVidas(), 0, "GameState::sem vidas");

    check(gameState.perderVida(), false, "GameState::nao perde vida abaixo de zero");
    check(gameState.getVidas(), 0, "GameState::vidas permanecem em zero");

    check(gameState.getPlayer().getName() == "Player", true, "GameState::possui Player");
    check(gameState.getWorld().getCurrentRegionType() == RegionType::Village, true, "GameState::World inicia em Village");

    GameState deathState("Player");

    check(deathState.estaGameOver(), false, "GameState::jogo inicia ativo");

    deathState.perderVida();
    check(deathState.estaGameOver(), false, "GameState::continua com 2 vidas");

    deathState.perderVida();
    check(deathState.estaGameOver(), false, "GameState::continua com 1 vida");

    deathState.perderVida();
    check(deathState.estaGameOver(), true, "GameState::Game Over sem vidas");

    GameState playerDeathState("Player");

    check(playerDeathState.getPlayer().estaVivo(), true, "GameState::Player inicia vivo");
    check(playerDeathState.getVidas(), 3, "GameState::Player inicia com 3 vidas");

    playerDeathState.getPlayer().receberDano(100);

    check(playerDeathState.getPlayer().estaVivo(), false, "GameState::Player morreu");

    if (!playerDeathState.getPlayer().estaVivo()) {
        playerDeathState.perderVida();
    }

    check(playerDeathState.getVidas(), 2, "GameState::morte remove uma vida");
    check(playerDeathState.estaGameOver(), false, "GameState::ainda nao e Game Over");

    // =========================================================
    // Character - movimento
    // =========================================================

    std::cout << "\n--- Character / Movimento ---\n";

    Character movingCharacter("MovingCharacter");

    movingCharacter.moverPara({ 3, 5 });

    check(movingCharacter.getPosicao().x, 3, "Character::posicao x");
    check(movingCharacter.getPosicao().y, 5, "Character::posicao y");

    movingCharacter.moverPara({ 8, 2 });

    check(movingCharacter.getPosicao().x, 8, "Character::nova posicao x");
    check(movingCharacter.getPosicao().y, 2, "Character::nova posicao y");

    return 0;
}

void check(int result, int expected, const std::string& testName)
{
    if (result == expected) {
        std::cout << "[PASS] " << testName << '\n';
    }
    else {
        std::cout << "[FAIL] " << testName << " | esperado: " << expected << " | recebido: " << result << '\n';
    }
}