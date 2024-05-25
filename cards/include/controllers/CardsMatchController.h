#pragma once
#include <vector>
#include <memory>

class Card;
class CardModel;

class CardsMatchController {
public:
    CardsMatchController();
	void addCard(const std::shared_ptr<Card>& inCard);
	void update();

private:
	std::vector<std::shared_ptr<Card>> cards;
	std::shared_ptr<CardModel> clickedModel;
	double lastClickTime = 0.0f;
    std::vector<std::shared_ptr<CardModel>> availableModels;

	void onCardClicked(Card* inCard);
	std::shared_ptr<CardModel> getCardModel(Card* inCard);
    std::shared_ptr<CardModel> getRandomAvailableModel();
};
