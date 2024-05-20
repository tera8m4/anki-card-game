#include "controllers/CardsMatchController.h"
#include "Card.h"
#include "components/BaseButtonComponent.h"
#include "models/CardModel.h"
#include "ModelsRegistry.h"

void CardsMatchController::addCard(const std::shared_ptr<Card>& inCard)
{
	if (!inCard) { return; }

	inCard->setModel(ModelsRegistry::getInstance().getModel(cards.size()));
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
	auto it = std::find(cards.begin(), cards.end(), inCard->shared_from_this());
	if (it != cards.end()) {
		const auto index = std::distance(cards.begin(), it);
		return ModelsRegistry::getInstance().getModel(index);
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
