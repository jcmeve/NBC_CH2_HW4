#pragma once
#include <string>
#include <map>
class PotionContainer {
protected:
    std::map<std::string, int> potionStock;
public:
    virtual void displayPotions()const;
    virtual void initializeStock(const std::string& potionName);
    bool popPotion(const std::string& potionName);

    virtual void pushPotion(const std::string& potionName);

    virtual int getStock(const std::string& potionName);
};