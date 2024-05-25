#include "controllers/CardsMatchController.h"
#include "Card.h"
#include "components/BaseButtonComponent.h"
#include "models/CardModel.h"
#include "ModelsRegistry.h"
#include <random>

CardsMatchController::CardsMatchController()
{
    availableModels = ModelsRegistry::getInstance().getCardModels();
}

void CardsMatchController::addCard(const std::shared_ptr<Card>& inCard)
{
	if (!inCard) { return; }

    
	inCard->setModel(getRandomAvailableModel());
	inCard->findComponent<BaseButtonComponent>()->onClickedCallback = [this](BaseButtonComponent* inButton)
		{
			onCardClicked(inButton->getOwner());
		};

	cards.push_back(inCard);
}

void CardsMatchController::onCardClicked(Card* inCard)
{
	std::shared_ptr<CardModel> model = getCardModel(inCard);

    if (!model)
    {
        return;
    }

    if (!clickedModel)
    {
		model->setIsFlipped(!model->getIsFlipped());

		clickedModel = model;
		lastClickTime = GetTime();
	}
    else
    {
        const std::string& matchingKey = model->getMatchingKey();
        if (clickedModel->getKey() == matchingKey)
        {
            clickedModel->setIsMatched(true);
            model->setIsMatched(true);
        }
        else {
            clickedModel->setIsFlipped(false);
            model->setIsFlipped(true);
            clickedModel = model;
        }
    }
}

std::shared_ptr<CardModel> CardsMatchController::getCardModel(Card* inCard)
{
    if (inCard)
    {
        return ModelsRegistry::getInstance().getModel(inCard->getModelKey());
    }
    return nullptr;
}

void CardsMatchController::update()
{
	if (clickedModel && lastClickTime + 1.0 < GetTime())
	{
		clickedModel->setIsFlipped(false);
		clickedModel.reset();
	}
}

std::shared_ptr<CardModel> CardsMatchController::getRandomAvailableModel()
{
    if (availableModels.empty()) {
        return nullptr;
    }

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, static_cast<int>(availableModels.size() - 1));

    const int index = dist(rng);
    auto model = availableModels[index];

    swap(availableModels.back(), availableModels[index]);
    availableModels.pop_back();

    return model;
}
