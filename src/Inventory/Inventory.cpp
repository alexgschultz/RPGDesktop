#include "rpg/Inventory/Inventory.hpp"

void Inventory::adicionar(const Item& item) {
    items.push_back(item);
}

int Inventory::quantidade() const {
    return static_cast<int>(items.size());
}

bool Inventory::remover(int indice) {
    if (indice >= 0 && indice < static_cast<int>(items.size())) {
        items.erase(items.begin() + indice);
        return true;
    }
    return false;
}

bool Inventory::usar(int indice, Character& character) {
	if (indice >= 0 && indice < static_cast<int>(items.size())) {
		Item& item = items[indice];
		if (item.getType() == ItemType::Cura) {
			character.recuperarVida(character.getVidaMaxima() / 2);
		}
		else if (item.getType() == ItemType::Mana) {
			character.recuperarMana(character.getManaMaxima() / 2);
		}
		remover(indice);
		return true;
	}
	return false;
}