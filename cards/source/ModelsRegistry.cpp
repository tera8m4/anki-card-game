#include "ModelsRegistry.h"

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
