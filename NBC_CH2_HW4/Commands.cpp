#include "Commands.h"
#include "AlchemyWorkshop.h"
#include <iostream>


void displayAllStocks(AlchemyWorkshop& myWorkshop) {
    myWorkshop.displayAllStock();
}

void displayPlayerInventory(PotionContainer& player) {
    player.displayPotions();
}

void returnPotion(AlchemyWorkshop& myWorkshop, PotionContainer& player) {
    std::string name;
    std::cout << "포션 이름: ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, name);
    myWorkshop.returnPotion(name, player);
}

void dispensePotionByName(AlchemyWorkshop& myWorkshop, PotionContainer& player) {
    std::string name;
    std::cout << "포션 이름: ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, name);
    myWorkshop.dispensePotionByName(name, player);
}

void dispensePotionByIngredient(AlchemyWorkshop& myWorkshop, PotionContainer& player) {
    std::string name;
    std::cout << "재료 이름: ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, name);
    myWorkshop.dispensePotionByIngredient(name, player);
}

void makePotionByIngredient(AlchemyWorkshop& myWorkshop, PotionContainer& player) {
    // 여러 재료를 입력받기 위한 로직
    std::vector<std::string> ingredients_input;
    std::string ingredient;
    std::cout << "사용할 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << std::endl;
    std::cin.ignore(10000, '\n');
    while (true) {
        std::cout << "재료 입력: ";
        std::getline(std::cin, ingredient);

        // 사용자가 '끝'을 입력하면 재료 입력 종료
        if (ingredient == "끝") {
            break;
        }
        ingredients_input.push_back(ingredient);
    }
    // 입력받은 재료가 하나 이상 있을 때만 조합 시도
    if (!ingredients_input.empty()) {
        myWorkshop.makePotionByIngredient(ingredients_input);
    }
    else {
        std::cout << ">> 재료가 입력되지 않아 포션 제조를 취소합니다." << std::endl;
    }


}


void exitWorkshop() {
    std::cout << "공방 문을 닫습니다..." << std::endl;
    exit(0);
}

void searchRecipeByIngredient(AlchemyWorkshop& myWorkshop) {
    std::string name;
    std::cout << "재료 이름: ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, name);

    std::vector<const PotionRecipe*> ret = myWorkshop.searchRecipeByIngredient(name);
    if (ret.empty()) {
        std::cout << "일치하는 레시피를 찾지 못했습니다." << std::endl;
        return;
    }
    for (const PotionRecipe* recipe : ret) {
        recipe->displayRecipe();
    }
}

void searchRecipeByName(AlchemyWorkshop& myWorkshop) {
    std::string name;
    std::cout << "물약 이름: ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, name);

    const PotionRecipe* ret = myWorkshop.searchRecipeByName(name);
    if (ret == nullptr) {
        std::cout << "일치하는 레시피를 찾지 못했습니다." << std::endl;
        return;
    }
    ret->displayRecipe();
}

void displayAllRecipes(AlchemyWorkshop& myWorkshop) {
    myWorkshop.displayAllRecipes();
}

void addRecipe(AlchemyWorkshop& myWorkshop) {
    std::string name;
    std::cout << "물약 이름: ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, name);

    // 여러 재료를 입력받기 위한 로직
    std::vector<std::string> ingredients_input;
    std::string ingredient;
    std::cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << std::endl;

    while (true) {
        std::cout << "재료 입력: ";
        std::getline(std::cin, ingredient);

        // 사용자가 '끝'을 입력하면 재료 입력 종료
        if (ingredient == "끝") {
            break;
        }
        ingredients_input.push_back(ingredient);
    }
    // 입력받은 재료가 하나 이상 있을 때만 레시피 추가
    if (!ingredients_input.empty()) {
        myWorkshop.addRecipe(name, ingredients_input);
    }
    else {
        std::cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
    }
}


void displayPlayerInventory(AlchemyWorkshop& myWorkshop, PotionContainer& player) { displayPlayerInventory(player); }

void displayAllStocks(AlchemyWorkshop& myWorkshop, PotionContainer& player) { displayAllStocks(myWorkshop); }

void exitWorkshop(AlchemyWorkshop& myWorkshop, PotionContainer& player) { exitWorkshop(); }

void searchRecipeByIngredient(AlchemyWorkshop& myWorkshop, PotionContainer& player) { searchRecipeByIngredient(myWorkshop); }

void searchRecipeByName(AlchemyWorkshop& myWorkshop, PotionContainer& player) { searchRecipeByName(myWorkshop); }

void displayAllRecipes(AlchemyWorkshop& myWorkshop, PotionContainer& player) { displayAllRecipes(myWorkshop); }

void addRecipe(AlchemyWorkshop& myWorkshop, PotionContainer& player) { addRecipe(myWorkshop); }
