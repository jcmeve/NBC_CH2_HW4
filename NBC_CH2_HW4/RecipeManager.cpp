#include "RecipeManager.h"
#include <iostream>
#include <set>
bool RecipeManager::addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
    if (recipes.find(name) != recipes.end()) {
        std::cout << "이미 습득한 레시피입니다." << std::endl;
        return false;
    }

    std::set<std::string> unique_ingredients(ingredients.begin(), ingredients.end());
    if (ingredients.size() != unique_ingredients.size()) {
        std::cout << "중복된 재료를 포함하는 레시피는 허용되지 않습니다." << std::endl;
        return false;
    }

    //result of recipe is unique
    std::map<std::string, int> counter;
    for (auto ingredient : ingredients) {
        for (const PotionRecipe* recipe : searchRecipeByIngredient(ingredient)) {
            ++counter[recipe->potionName];
        }
    }
    for (auto& pair : counter) {//조합식의 결과물은 유일하다고 가정
        if (pair.second == ingredients.size()
            && searchRecipeByName(pair.first)->ingredients.size() == ingredients.size()) {
            std::cout << "완전히 동일한 재료를 요구하는 레시피가 있어 레시피 추가를 취소합니다.";
            return false;
        }
    }



    auto res = recipes.emplace(name, PotionRecipe(name, ingredients));
    PotionRecipe* ptr = &res.first->second;

    for (std::string ingredient : unique_ingredients) {
        indeces[ingredient].push_back(ptr);
    }

    std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다." << std::endl;
    return true;
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
