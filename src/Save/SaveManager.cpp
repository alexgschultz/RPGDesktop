#include "rpg/Save/SaveManager.hpp"
#include <fstream>
#include <utility>
#include <charconv>

namespace
{
    std::expected<int, std::string> parseInt(const std::string& value, const std::string& field)
    {
        int parsedValue{};

        auto [ptr, ec] = std::from_chars(
            value.data(),
            value.data() + value.size(),
            parsedValue
        );

        if (ec != std::errc{} || ptr != value.data() + value.size()) {
            return std::unexpected("Valor invalido para " + field);
        }

        return parsedValue;
    }
}

SaveData SaveManager::criarSaveData(const GameState& gameState) const {
    return SaveData{
        .playerName = gameState.getPlayer().getName(),
        .vida = gameState.getPlayer().getVida(),
        .mana = gameState.getPlayer().getMana(),
        .level = gameState.getPlayer().getLevel(),
        .experiencia = gameState.getPlayer().getExperiencia(),
        .vidas = gameState.getVidas(),
        .region = gameState.getWorld().getCurrentRegionType(),
        .items = gameState.getPlayer().getInventory().getItems()
    };
}

bool SaveManager::save(const SaveData& data, const std::filesystem::path& path) const
{
    std::ofstream file(path);

    if (!file) {
        return false;
    }

    file << "playerName=" << data.playerName << '\n';
    file << "vida=" << data.vida << '\n';
    file << "mana=" << data.mana << '\n';
    file << "level=" << data.level << '\n';
    file << "experiencia=" << data.experiencia << '\n';
    file << "vidas=" << data.vidas << '\n';
    file << "region=" << std::to_underlying(data.region) << '\n';

    for (const auto& item : data.items) {
        file << "item=" << std::to_underlying(item.getType()) << '|' << item.getName() << '\n';
    }

    return file.good();
}

std::expected<SaveData, std::string> SaveManager::load(const std::filesystem::path& path) const
{
    std::ifstream file(path);

    if (!file) {
        return std::unexpected("Nao foi possivel abrir o arquivo de save");
    }

    SaveData data;

    std::string line;

    while (std::getline(file, line)) {
        auto position = line.find('=');

        if (position == std::string::npos) {
            continue;
        }

        std::string key = line.substr(0, position);
        std::string value = line.substr(position + 1);

        if (key == "playerName") {
            data.playerName = value;
        }
        else if (key == "vida") {
            auto parsed = parseInt(value, "vida");

            if (!parsed) {
                return std::unexpected(parsed.error());
            }

            data.vida = *parsed;
        
        }
        else if (key == "mana") {
            auto parsed = parseInt(value, "mana");

            if (!parsed) {
                return std::unexpected(parsed.error());
            }

            data.mana = *parsed;
        }
        else if (key == "level") {
            auto parsed = parseInt(value, "level");

            if (!parsed) {
                return std::unexpected(parsed.error());
            }

            data.level = *parsed;
        }
        else if (key == "experiencia") {
            auto parsed = parseInt(value, "experiencia");

            if (!parsed) {
                return std::unexpected(parsed.error());
            }

            data.experiencia = *parsed;
        }
        else if (key == "vidas") {
            auto parsed = parseInt(value, "vidas");

            if (!parsed) {
                return std::unexpected(parsed.error());
            }

            data.vidas = *parsed;
        }
        else if (key == "region") {
            auto parsed = parseInt(value, "region");

            if (!parsed) {
                return std::unexpected(parsed.error());
            }

            switch (*parsed) {
                case std::to_underlying(RegionType::Village):
                    data.region = RegionType::Village;
                    break;
                case std::to_underlying(RegionType::Forest):
                    data.region = RegionType::Forest;
                    break;
                case std::to_underlying(RegionType::Cave):
                    data.region = RegionType::Cave;
                    break;
                default:
                    return std::unexpected("Valor inválido para 'region'");
            }
        }
        else if (key == "item") {
            auto separator = value.find('|');

            if (separator == std::string::npos) {
                return std::unexpected("Formato invalido para item");
            }

            std::string typeText = value.substr(0, separator);
            std::string name = value.substr(separator + 1);

            auto parsedType = parseInt(typeText, "item");

            if (!parsedType) {
                return std::unexpected(parsedType.error());
            }

            switch (*parsedType) {
                case std::to_underlying(ItemType::Cura):
                    data.items.emplace_back(name, ItemType::Cura);
                    break;

                case std::to_underlying(ItemType::Mana):
                    data.items.emplace_back(name, ItemType::Mana);
                    break;

                default:
                    return std::unexpected("Valor invalido para tipo de item");
            }
        }
    }

    return data;
}

GameState SaveManager::criarGameState(const SaveData& data) const
{
    GameState gameState(data.playerName);

    gameState.getPlayer().restaurarEstado(data.vida, data.mana);
    gameState.getPlayer().restaurarProgressao(data.level, data.experiencia);
    gameState.getPlayer().getInventory().restaurar(data.items);

    gameState.restaurarVidas(data.vidas);
    gameState.getWorld().changeRegion(data.region);

    return gameState;
}

std::expected<GameState, std::string> SaveManager::loadGameState(
    const std::filesystem::path& path) const
{
    auto data = load(path);

    if (!data) {
        return std::unexpected(data.error());
    }

    return criarGameState(*data);
}