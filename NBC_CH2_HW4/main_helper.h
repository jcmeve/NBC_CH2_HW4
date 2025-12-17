#pragma once
#include<array>
class AlchemyWorkshop;
class PotionContainer;

/*  How to add feature
    1. add ECmd
    2. make function /
        2.1 make def in main_helper.cpp 
        2.2 make wrapping function like void(*)(AlchemyWorkshop&, PotionContainer&) at end of main_helper.cpp 
        2.3 Declaration  here
    3. bind function to ECmd
    4. write explain
    4. well done

*/

//wrap
void addRecipe(AlchemyWorkshop& myWorkshop, PotionContainer& player);

void displayAllRecipes(AlchemyWorkshop& myWorkshop, PotionContainer& player);

void searchRecipeByName(AlchemyWorkshop& myWorkshop, PotionContainer& player);

void searchRecipeByIngredient(AlchemyWorkshop& myWorkshop, PotionContainer& player);

void exitWorkshop(AlchemyWorkshop& myWorkshop, PotionContainer& player);

void displayAllStocks(AlchemyWorkshop& myWorkshop, PotionContainer& player);

void dispensePotion(AlchemyWorkshop& myWorkshop, PotionContainer& player);

void returnPotion(AlchemyWorkshop& myWorkshop, PotionContainer& player);

void displayPlayerInventory(AlchemyWorkshop& myWorkshop, PotionContainer& player);


enum class ECmd {
    BEGIN_OF_ENUM, ADD, PRINT_RECIPES, PRINT_STOCKS, PRINT_INVENTORY, SEARCH_NAME, SEARCH_INGREDIENT, DISPENSE, RETURN, EXIT, END_OF_ENUM
};
constexpr int ECmd_SIZE = static_cast<int>(ECmd::END_OF_ENUM);


constexpr std::array<const char*, ECmd_SIZE> ECmd_to_Explain_Init() {
    std::array<const char*, ECmd_SIZE> arr = {};
    arr[(int)ECmd::ADD] = "레시피 추가";
    arr[(int)ECmd::PRINT_RECIPES] = "모든 레시피 출력";
    arr[(int)ECmd::PRINT_STOCKS] = "모든 재고 출력";
    arr[(int)ECmd::PRINT_INVENTORY] = "플레이어 포션 출력";
    arr[(int)ECmd::DISPENSE] = "포션 지급받기";
    arr[(int)ECmd::RETURN] = "포션 반환하기";
    arr[(int)ECmd::EXIT] = "종료";
    arr[(int)ECmd::SEARCH_NAME] = "이름으로 검색";
    arr[(int)ECmd::SEARCH_INGREDIENT] = "재료로 검색";
    return arr;
}
constexpr std::array<void(*)(AlchemyWorkshop&, PotionContainer&), ECmd_SIZE> ECmd_to_Func_Init() {
    std::array<void(*)(AlchemyWorkshop&, PotionContainer&), ECmd_SIZE> arr = {};
    arr[(int)ECmd::ADD] = addRecipe;// "레시피 추가";
    arr[(int)ECmd::PRINT_RECIPES] = displayAllRecipes;
    arr[(int)ECmd::PRINT_STOCKS] = displayAllStocks;
    arr[(int)ECmd::PRINT_INVENTORY] = displayPlayerInventory;
    arr[(int)ECmd::DISPENSE] = dispensePotion;
    arr[(int)ECmd::RETURN] = returnPotion;
    arr[(int)ECmd::EXIT] = exitWorkshop;
    arr[(int)ECmd::SEARCH_NAME] = searchRecipeByName;
    arr[(int)ECmd::SEARCH_INGREDIENT] = searchRecipeByIngredient;
    return arr;
}

constexpr std::array<const char*, ECmd_SIZE> ECmd_to_Explain = ECmd_to_Explain_Init();
constexpr std::array<void(*)(AlchemyWorkshop&, PotionContainer&), ECmd_SIZE>  ECmd_to_Func = ECmd_to_Func_Init();

