#include <iostream>
#include <vector>
#include <array>
#include <string>

#include "AlchemyWorkshop.h"
#include "Commands.h"



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
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        if (auto fp = ECmd_to_Func[choice])
            fp(myWorkshop, player);
        else {
            std::cout << "ECmd_to_Func 초기화 오류" << std::endl;
            exit(-1);
        }
    }

    return 0;
}

//질문
// 1. 개발 프로세스 가이드에 있는 기반 코드를 기준으로 main함수를 만들었는데 도전기능 가이드에 있는 main함수와 너무 달라 평가에 영향이 없을지 우려됨(Potion Container 추가로 Player 인벤토리 따로 빠지는 등 )
// 
// 
// 2. 조합이라는 키워드가 들어가 있어서 재료들을 던져주면 정확히 일치하는 포션을 만들어 제고에 추가하려고 했는데
// 제공된 힌트 테스트코드 내용을 보니 재료 하나를 특정하고 해당 재료를 포함하는 포션을 모두 지급받는 것으로 되어있어 헷갈림



//void main() {
//    AlchemyWorkshop workshop;
//
//    workshop.addRecipe("Healing Potion", { "Herb", "Water" });
//    workshop.addRecipe("Mana Potion", { "Magic Water", "Crystal" });
//    workshop.addRecipe("Stamina Potion", { "Herb", "Berry" });
//    workshop.addRecipe("Fire Resistance Potion", { "Fire Flower", "Ash" });
//
//    std::cout << "=== 초기 상태 (레시피 추가 + 재고 자동 3개) ===\n";
//    workshop.displayAllRecipes();
//
//    std::cout << "\n[재고 확인] Healing Potion 재고: "
//        << workshop.getStock("Healing Potion") << "\n";
//    std::cout << "\n=== 이름으로 지급 테스트 (Healing Potion 3회 지급) ===\n";
//    std::cout << "1회 지급: " << (workshop.DispensePotionByName("Healing Potion") ? "성공" : "실패") << "\n";
//    std::cout << "2회 지급: " << (workshop.DispensePotionByName("Healing Potion") ? "성공" : "실패") << "\n";
//    std::cout << "3회 지급: " << (workshop.DispensePotionByName("Healing Potion") ? "성공" : "실패") << "\n";
//
//    std::cout << "현재 재고: " << workshop.GetStockByName("Healing Potion") << "\n";
//
//    std::cout << "4회 지급(재고 없으면 실패): "
//        << (workshop.DispensePotionByName("Healing Potion") ? "성공" : "실패") << "\n";
//
//    std::cout << "\n=== 재료로 지급 테스트 (ingredient = Herb) ===\n";
//    std::vector<std::string> dispensed = workshop.DispensePotionsByIngredient("Herb");
//
//    std::cout << "지급된 물약 수: " << dispensed.size() << "\n";
//    for (const std::string& name : dispensed)
//        std::cout << "- " << name << "\n";
//
//    std::cout << "\n=== 공병 반환 테스트 (Healing Potion) ===\n";
//    workshop.ReturnPotionByName("Healing Potion");
//    workshop.ReturnPotionByName("Healing Potion");
//    workshop.ReturnPotionByName("Healing Potion"); // 이미 3이면 더 올라가면 안 됨
//
//    std::cout << "반환 후 재고(최대 3 유지): "
//        << workshop.GetStockByName("Healing Potion") << "\n";
//
//    std::cout << "\n=== 최종 상태 ===\n";
//    workshop.displayAllRecipes();
// 
//}
//   
