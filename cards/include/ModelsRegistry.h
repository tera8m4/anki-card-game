#pragma once

#include <memory>
#include <vector>

class CardModel;

class ModelsRegistry {
public:
	static ModelsRegistry& getInstance();

	void addCardModel(const std::shared_ptr<CardModel>& inModel);
	std::shared_ptr<CardModel> getModel(const std::size_t inIndex);

private:
	ModelsRegistry() = default;

	std::vector<std::shared_ptr<CardModel>> cardModels;
};