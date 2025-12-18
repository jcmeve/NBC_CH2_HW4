#pragma once
#include "PotionContainer.h"
#include <vector>
class StockManager : public PotionContainer {
private:
    constexpr static int MAX_STOCK = 3;
public:
    void initializeStock(const std::string& potionName) override;

    void pushPotion(const std::string& potionName) override;
};