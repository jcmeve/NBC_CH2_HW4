#include "PotionRecipe.h"
#include<iostream>
// 생성자: 재료 목록을 받아 초기화하도록 수정
PotionRecipe::PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
    : potionName(name), ingredients(ingredients) {
}

void PotionRecipe::displayRecipe() const {
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
