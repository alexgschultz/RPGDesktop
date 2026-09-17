#pragma once
#include "rpg/Game/GameState.hpp"
#include "rpg/Save/SaveData.hpp"
#include <filesystem>
#include <expected>
#include <string>

class SaveManager
{
public:
    SaveData criarSaveData(const GameState& gameState) const;
    bool save(const SaveData& data, const std::filesystem::path& path) const;
    std::expected<SaveData, std::string> load(const std::filesystem::path& path) const;
    GameState criarGameState(const SaveData& data) const;
    std::expected<GameState, std::string> loadGameState(const std::filesystem::path& path) const;
};