#include "StockManager.h"
#include <iostream>
void StockManager::initializeStock(const std::string& potionName) {
    if (potionStock.find(potionName) != potionStock.end()) {
        std::cout << "이미 소지한 포션입니다." << std::endl;
        return;
    }
    potionStock[potionName] = MAX_STOCK;
}

void StockManager::pushPotion(const std::string& potionName) {
    PotionContainer::pushPotion(potionName);
    if (potionStock[potionName] > MAX_STOCK) {
        potionStock[potionName] = MAX_STOCK;
        std::cout << "보관 한도를 초과해 아이템을 파괴합니다." << std::endl;
    }
}
