#include "PotionContainer.h"
#include <iostream>
void PotionContainer::displayPotions() const {
    if (potionStock.empty()) {
        std::cout << "보유한 포션이 없습니다." << std::endl;
    }
    for (const auto pair : potionStock) {
        std::cout << pair.first << " " << pair.second << "개 보유" << std::endl;
    }
    std::cout << std::endl;
}

void PotionContainer::initializeStock(const std::string& potionName) {
    if (potionStock.find(potionName) != potionStock.end()) {
        std::cout << "이미 소지한 포션입니다." << std::endl;
        return;
    }
    potionStock[potionName] = 0;
}

bool PotionContainer::popPotion(const std::string& potionName) {
    if (getStock(potionName) == -1) {
        return false;
    }
    --potionStock[potionName];
    if (potionStock[potionName] == 0) {
        potionStock.erase(potionName);
    }
    return true;
}

void PotionContainer::pushPotion(const std::string& potionName) {
    if (potionStock.find(potionName) == potionStock.end()) {
        potionStock[potionName] = 1;
        return;
    }
    ++potionStock[potionName];
}

int PotionContainer::getStock(const std::string& potionName) {
    if (potionStock.find(potionName) == potionStock.end()) {
        std::cout << "재고가 없는 포션입니다." << std::endl;
        return -1;
    }
    return potionStock[potionName];
}
