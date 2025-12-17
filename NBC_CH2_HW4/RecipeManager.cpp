#include "RecipeManager.h"
#include <iostream>
#include <set>
void RecipeManager::addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
    if (recipes.find(name) != recipes.end()) {
        std::cout << "이미 습득한 레시피입니다." << std::endl;
        return;
    }

    auto res = recipes.emplace(name, PotionRecipe(name, ingredients));
    PotionRecipe* ptr = &res.first->second;
    std::set<std::string> unique_ingredients(ingredients.begin(), ingredients.end());
    for (std::string ingredient : unique_ingredients) {
        indeces[ingredient].push_back(ptr);
    }
    //TODO 모든 재료가 같은 레시피가 존재하면 안됨

    std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다." << std::endl;
}

void RecipeManager::displayAllRecipes() const {
    if (recipes.empty()) {
        std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
        return;
    }

    std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
    for (const auto& pair : recipes) {
        pair.second.displayRecipe();
    }
    std::cout << "---------------------------\n";
}

const PotionRecipe* RecipeManager::searchRecipeByName(const std::string& name) const {
    auto iter = recipes.find(name);
    if (iter == recipes.end()) {
        return nullptr;
    }
    return &iter->second;
}

const std::vector<const PotionRecipe*> RecipeManager::searchRecipeByIngredient(const std::string& name) const {
    auto iter = indeces.find(name);
    if (iter == indeces.end()) {
        return {};
    }
    return std::vector<const PotionRecipe*>(iter->second.begin(), iter->second.end());

}

const std::vector<const PotionRecipe*> RecipeManager::getAllRecipes() const {
    std::vector<const PotionRecipe*> ret;
    ret.reserve(recipes.size());
    for (auto& pair : recipes) {
        ret.push_back(&pair.second);
    }
    return ret;
}
