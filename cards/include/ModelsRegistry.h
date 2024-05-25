#pragma once

#include <memory>
#include <vector>
#include <string>

class CardModel;
struct CardInfo;

class ModelsRegistry {
public:
	static ModelsRegistry& getInstance();

	void addCardModel(const std::shared_ptr<CardModel>& inModel);
	std::shared_ptr<CardModel> getModel(const std::size_t inIndex);
    std::shared_ptr<CardModel> getModel(const std::string& inKey);
    const std::vector<std::shared_ptr<CardModel>>& getCardModels() const;
    void createFromCardInfos(const std::vector<CardInfo>& inCardInfos);

private:
	ModelsRegistry() = default;

	std::vector<std::shared_ptr<CardModel>> cardModels;
};
