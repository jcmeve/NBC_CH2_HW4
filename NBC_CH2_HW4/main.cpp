#include <iostream>
#include <vector>
#include <array>
#include <string>

#include "AlchemyWorkshop.h"
#include "main_helper.h"



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
            exit(-1);
        }
    }

    return 0;
}
