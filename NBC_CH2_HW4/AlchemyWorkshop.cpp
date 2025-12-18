#include "AlchemyWorkshop.h"

// addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
void AlchemyWorkshop::addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
    if(recipeManager.addRecipe(name, ingredients))
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

bool AlchemyWorkshop::dispensePotionByName(const std::string& potionName, PotionContainer& container) {
    bool ret = stockManager.popPotion(potionName);
    if (ret) {
        container.pushPotion(potionName);
    }
    return ret;
}

bool AlchemyWorkshop::dispensePotionByIngredient(const std::string& name, PotionContainer& container) {

    const std::vector<const PotionRecipe*> ret = recipeManager.searchRecipeByIngredient(name);
    if (ret.empty()) return false;
    for (const PotionRecipe* recipe : ret) {
        dispensePotionByName(recipe->potionName, container);
    }
    return true;
}

bool AlchemyWorkshop::makePotionByIngredient(const std::vector<std::string>& ingredients) {
    if (ingredients.empty()) {
        return false;
    }

    //비트맵을 쓰면 좀 더 빠르지만 포션을 string으로 주어진 것을 고려해 크게 변경하지 않았음
    //완벽한 조합식을 요구하기 때문에 소유한 모든 아이템을 검사해 제조가능한 대상을 찾는것은 불가능함
    //해당 기능은 아이템이 추가될 때 마다 업데이트 해줘야 하고 순환제조 혹은 상상위 제조 등이 있다면 해당 사항도 고려해야함.
    std::map<std::string, int> counter;
    for (auto ingredient : ingredients) {
        for (const PotionRecipe* recipe : recipeManager.searchRecipeByIngredient(ingredient)) {
            ++counter[recipe->potionName];
        }
    }
    for (auto& pair : counter) {//조합식의 결과물은 유일하다고 가정
        if (pair.second == ingredients.size()
            && recipeManager.searchRecipeByName(pair.first)->ingredients.size() == ingredients.size()) {
            stockManager.pushPotion(pair.first);
            return true;

        }
    }

    return false;
}

void AlchemyWorkshop::returnPotion(std::string& potionName, PotionContainer& container) {
    bool ret = container.popPotion(potionName);
    if (ret) {
        stockManager.pushPotion(potionName);
    }
}

int AlchemyWorkshop::getStock(const std::string& potionName) const {
    return stockManager.getStock(potionName);
}
