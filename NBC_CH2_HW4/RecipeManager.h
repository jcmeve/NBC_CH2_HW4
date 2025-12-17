#pragma once
#include <map>
#include<string>
#include"PotionRecipe.h"
class RecipeManager {
private:
    std::map<std::string, PotionRecipe> recipes;
    std::map<std::string, std::vector<PotionRecipe*>> indeces;
public:
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients);

    void displayAllRecipes() const;

    const PotionRecipe* searchRecipeByName(const std::string& name) const;

    const std::vector<const PotionRecipe*> searchRecipeByIngredient(const std::string& name) const;

    const std::vector<const PotionRecipe*> getAllRecipes() const;

};