#include "AlchemyWorkshop.h"

// addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
void AlchemyWorkshop::addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
    recipeManager.addRecipe(name, ingredients);
    stockManager.initializeStock(name);
}

// 모든 레시피 출력 메서드
void AlchemyWorkshop::displayAllRecipes() const {
    recipeManager.displayAllRecipes();
}

const PotionRecipe* AlchemyWorkshop::searchRecipeByName(const std::string& name) const {
    return recipeManager.searchRecipeByName(name);
}

const std::vector<const PotionRecipe*> AlchemyWorkshop::searchRecipeByIngredient(const std::string& name) const {
    return recipeManager.searchRecipeByIngredient(name);
}

const std::vector<const PotionRecipe*> AlchemyWorkshop::getAllRecipes() const {
    return recipeManager.getAllRecipes();
}

void AlchemyWorkshop::displayAllStock() const {
    stockManager.displayPotions();
}

bool AlchemyWorkshop::dispensePotion(std::string& potionName, PotionContainer& container) {
    bool ret = stockManager.popPotion(potionName);
    if (ret) {
        container.pushPotion(potionName);
    }
    return ret;
}

void AlchemyWorkshop::returnPotion(std::string& potionName, PotionContainer& container) {
    bool ret = container.popPotion(potionName);
    if (ret) {
        stockManager.pushPotion(potionName);
    }
}

int AlchemyWorkshop::getStock(std::string& potionName) {
    return stockManager.getStock(potionName);
}
