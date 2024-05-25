#include "ModelsRegistry.h"
#include "models/CardModel.h"
#include "CardInfo.h"

#include <iostream>
#include <chrono>
#include <random>
#include <functional>
#include <sstream>

namespace {
    std::string generatePseudoUniqueId() {
        // Get current time in nanoseconds
        auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
        auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(now).count();

        // Generate a random number
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<uint64_t> dis;

        uint64_t random_number = dis(gen);

        // Combine time and random number
        std::stringstream ss;
        ss << nanoseconds << random_number;

        // Hash the combined string
        std::hash<std::string> hasher;
        size_t hash = hasher(ss.str());

        // Convert hash to hex string
        std::stringstream hex_ss;
        hex_ss << std::hex << hash;

        return hex_ss.str();
    }
}

ModelsRegistry& ModelsRegistry::getInstance()
{
	static ModelsRegistry instance;

	return instance;
}

void ModelsRegistry::addCardModel(const std::shared_ptr<CardModel>& inModel)
{
	cardModels.push_back(inModel);
}

std::shared_ptr<CardModel> ModelsRegistry::getModel(const std::size_t inIndex)
{
	if (inIndex >= 0 && inIndex < cardModels.size()) {
		return cardModels[inIndex];
	}

	return nullptr;
}

std::shared_ptr<CardModel> ModelsRegistry::getModel(const std::string& inKey)
{
    for (const auto& x : cardModels)
    {
        if (x->getKey() == inKey) {
            return x;
        }
    }

    return nullptr;
}

void ModelsRegistry::createFromCardInfos(const std::vector<CardInfo>& inCardInfos)
{
    for (const auto& cardInfo : inCardInfos) {
        const auto& meaningKey = generatePseudoUniqueId();
        const auto& wordKey = generatePseudoUniqueId();

        cardModels.push_back(std::make_shared<CardModel>(cardInfo.meaning, meaningKey, wordKey));
        cardModels.push_back(std::make_shared<CardModel>(cardInfo.word, wordKey, meaningKey));
    }
    
}


const std::vector<std::shared_ptr<CardModel>>& ModelsRegistry::getCardModels() const
{
    return cardModels;
}
