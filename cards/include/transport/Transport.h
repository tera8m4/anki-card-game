#pragma once
#include <vector>
#include <string>
#include "CardInfo.h"

class Transport {
public:
    static Transport& getInstance();
    std::vector<unsigned long long> findDueCards();
    std::vector<std::string> getWords(const std::vector<unsigned long long>& inCardIds);
    std::vector<CardInfo> getCardInfo(const std::vector<std::string>& inCardIds);

private:
    Transport() = default;
};
