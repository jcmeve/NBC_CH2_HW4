#pragma once
#include "StockManager.h"
#include "RecipeManager.h"
// AlchemyWorkshop 클래스: 레시피 목록을 관리
class AlchemyWorkshop {
private:
    StockManager stockManager;
    RecipeManager recipeManager;
public:
    // addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients);

    // 모든 레시피 출력 메서드
    void displayAllRecipes() const;

    const PotionRecipe* searchRecipeByName(const std::string& name)const;

    const std::vector<const PotionRecipe*> searchRecipeByIngredient(const std::string& name)const;

    const std::vector<const PotionRecipe*> getAllRecipes() const;

    void displayAllStock() const;

    bool dispensePotionByName(const std::string& potionName, PotionContainer& container);
    bool dispensePotionByIngredient(const std::string& name, PotionContainer& container);
    void returnPotion(std::string& potionName, PotionContainer& container);
    int getStock(const std::string& potionName)const;

};