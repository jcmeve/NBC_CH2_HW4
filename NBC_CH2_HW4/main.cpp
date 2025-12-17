#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <map>
#include <algorithm>
#include <set>


// PotionRecipe 클래스: 재료 목록을 vector<string>으로 변경
class PotionRecipe {
public:
    std::string potionName;
    std::vector<std::string> ingredients; // 단일 재료에서 재료 '목록'으로 변경

    // 생성자: 재료 목록을 받아 초기화하도록 수정
    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : potionName(name), ingredients(ingredients) {
    }
    void displayRecipe()const {
        std::cout << "- 물약 이름: " << potionName << std::endl;
        std::cout << "  > 필요 재료: ";

        // 재료 목록을 순회하며 출력
        for (size_t j = 0; j < ingredients.size(); ++j) {
            std::cout << ingredients[j];
            // 마지막 재료가 아니면 쉼표로 구분
            if (j < ingredients.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
};

class RecipeManager {
private:
    std::map<std::string, PotionRecipe> recipes;
    std::map<std::string, std::vector<PotionRecipe*>> indeces;
public:
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        if (recipes.find(name) != recipes.end()) {
            std::cout << "이미 습득한 레시피입니다." << std::endl;
            return;
        }

        auto res = recipes.emplace(name,PotionRecipe(name, ingredients));
        PotionRecipe* ptr = &res.first->second;
        std::set<std::string> unique_ingredients(ingredients.begin(), ingredients.end());
        for (std::string ingredient : unique_ingredients) {
            indeces[ingredient].push_back(ptr);
        }
        //TODO 모든 재료가 같은 레시피가 존재하면 안됨

        std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다." << std::endl;
    }

    void displayAllRecipes() const {
        if (recipes.empty()) {
            std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
            return;
        }

        std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
        for (const auto &pair : recipes) {
            pair.second.displayRecipe();
        }
        std::cout << "---------------------------\n";
    }

    const PotionRecipe* searchRecipeByName(const std::string& name) const {
        auto iter = recipes.find(name);
        if (iter == recipes.end()) {
            return nullptr;
        }
        return &iter->second;
    }    

    const std::vector<const PotionRecipe*> searchRecipeByIngredient(const std::string& name) const {
        auto iter = indeces.find(name);
        if (iter == indeces.end()) {
            return {};
        }
        return std::vector<const PotionRecipe*>(iter->second.begin(), iter->second.end());

    }

    const std::vector<const PotionRecipe*> getAllRecipes() const {
        std::vector<const PotionRecipe*> ret;
        ret.reserve(recipes.size());
        for (auto& pair : recipes) {
            ret.push_back(&pair.second);
        }
        return ret;
    }

};


class PotionContainer {
protected:
    std::map<std::string, int> potionStock;
public:
    virtual void displayPotions()const {
        if (potionStock.empty()) {
            std::cout << "보유한 포션이 없습니다." << std::endl;
        }
        for (const auto pair : potionStock) {
            std::cout << pair.first << " " << pair.second << "개 보유" << std::endl;
        }
        std::cout << std::endl;
    }
    virtual void initializeStock(const std::string& potionName) {
        if (potionStock.find(potionName) != potionStock.end()) {
            std::cout << "이미 소지한 포션입니다." << std::endl;
            return;
        }
        potionStock[potionName] = 0;
    }
    bool popPotion(const std::string& potionName) {
        if (getStock(potionName) == -1) {
            return false;
        }
        --potionStock[potionName];
        if (potionStock[potionName] == 0) {
            potionStock.erase(potionName);
        }
        return true;
    }

    virtual void pushPotion(const std::string& potionName) {
        if (potionStock.find(potionName) == potionStock.end()) {
            potionStock[potionName] = 1;
            return;
        }
        ++potionStock[potionName];
    }

    virtual int getStock(const std::string& potionName) {
        if (potionStock.find(potionName) == potionStock.end()) {
            std::cout << "재고가 없는 포션입니다." << std::endl;
            return -1;
        }
        return potionStock[potionName];
    }
};

class StockManager : public PotionContainer {
private:
    constexpr static int MAX_STOCK = 3;
public:
    void initializeStock(const std::string& potionName) override {
        if (potionStock.find(potionName) != potionStock.end()) {
            std::cout << "이미 소지한 포션입니다." << std::endl;
            return;
        }
        potionStock[potionName] = MAX_STOCK;
    }

    void pushPotion(const std::string& potionName) override {
        PotionContainer::pushPotion(potionName);
        if (potionStock[potionName] > MAX_STOCK) {
            potionStock[potionName] = MAX_STOCK;
            std::cout << "보관 한도를 초과해 아이템을 파괴합니다." << std::endl;
        }
    }


};

// AlchemyWorkshop 클래스: 레시피 목록을 관리
class AlchemyWorkshop {
private:
    StockManager stockManager;
    RecipeManager recipeManager;
public:
    // addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        recipeManager.addRecipe(name, ingredients);
        stockManager.initializeStock(name);
    }

    // 모든 레시피 출력 메서드
    void displayAllRecipes() const {
        recipeManager.displayAllRecipes();
    }

    const PotionRecipe* searchRecipeByName(const std::string& name)const {
        return recipeManager.searchRecipeByName(name);
    }

    const std::vector<const PotionRecipe*> searchRecipeByIngredient(const std::string& name)const {
        return recipeManager.searchRecipeByIngredient(name);
    }

    const std::vector<const PotionRecipe*> getAllRecipes() const{
        return recipeManager.getAllRecipes();
    }

    void displayAllStock() const {
        stockManager.displayPotions();
    }

    bool dispensePotion(std::string& potionName, PotionContainer& container) {
        bool ret = stockManager.popPotion(potionName);
        if (ret) {
            container.pushPotion(potionName);
        }
        return ret;
    }
    void returnPotion(std::string& potionName, PotionContainer& container) {
        bool ret = container.popPotion(potionName);
        if (ret) {
            stockManager.pushPotion(potionName);
        }
    }
    int getStock(std::string& potionName) {
        return stockManager.getStock(potionName);
    }

};

void addRecipe(AlchemyWorkshop& myWorkshop);
void addRecipe(AlchemyWorkshop& myWorkshop, PotionContainer& player) { addRecipe(myWorkshop); }

void displayAllRecipes(AlchemyWorkshop& myWorkshop);
void displayAllRecipes(AlchemyWorkshop& myWorkshop, PotionContainer& player) { displayAllRecipes(myWorkshop); }

void searchRecipeByName(AlchemyWorkshop& myWorkshop);
void searchRecipeByName(AlchemyWorkshop& myWorkshop, PotionContainer& player) { searchRecipeByName(myWorkshop); }

void searchRecipeByIngredient(AlchemyWorkshop& myWorkshop);
void searchRecipeByIngredient(AlchemyWorkshop& myWorkshop, PotionContainer& player) { searchRecipeByIngredient(myWorkshop); }

void exitWorkshop();
void exitWorkshop(AlchemyWorkshop& myWorkshop, PotionContainer& player) { exitWorkshop(); }

void displayAllStocks(AlchemyWorkshop& myWorkshop);
void displayAllStocks(AlchemyWorkshop& myWorkshop, PotionContainer& player) { displayAllStocks(myWorkshop); }

void dispensePotion(AlchemyWorkshop& myWorkshop, PotionContainer& player);

void returnPotion(AlchemyWorkshop& myWorkshop, PotionContainer& player);

void displayPlayerInventory(PotionContainer& player);
void displayPlayerInventory(AlchemyWorkshop& myWorkshop, PotionContainer& player) { displayPlayerInventory(player); }



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

constexpr std::array<const char*, ECmd_SIZE> ECmd_to_Explain = ECmd_to_Explain_Init();

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

constexpr std::array<void(*)(AlchemyWorkshop&, PotionContainer&), ECmd_SIZE>  ECmd_to_Func = ECmd_to_Func_Init();



int main() {
    AlchemyWorkshop myWorkshop;
    PotionContainer player;
    while (true) {
        std::cout << "⚗️ 연금술 공방 관리 시스템" << std::endl;

        for (int i = (int)ECmd::BEGIN_OF_ENUM + 1; i < ECmd_to_Explain.size(); ++i) {
            std::cout << i << ". " << ECmd_to_Explain[i] << std::endl;
        }
        std::cout << "선택: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        ECmd cmd = (ECmd)choice;
        if (cmd <= ECmd::BEGIN_OF_ENUM || cmd >= ECmd::END_OF_ENUM) {
            std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
            continue;
        }
        if (auto fp = ECmd_to_Func[choice])
            fp(myWorkshop, player);
        else {
            std::cout << "ECmd_to_Func 초기화 오류" << std::endl;
        }
    }

    return 0;
}

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

void dispensePotion(AlchemyWorkshop& myWorkshop, PotionContainer& player) {
    std::string name;
    std::cout << "포션 이름: ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, name);
    bool ret = myWorkshop.dispensePotion(name, player);
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
