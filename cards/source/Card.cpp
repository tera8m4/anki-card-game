#include "Card.h"
#include "models/CardModel.h"
#include "components/BaseButtonComponent.h"


namespace {
	Vector2 CARD_SIZE{ .x = 100, .y = 150 };
}

Card::Card()
{
	components.push_back(std::make_unique<BaseButtonComponent>(this));
}


void Card::setModel(const std::shared_ptr<CardModel>& inModel)
{
	model = inModel;
}

void Card::setPosition(const Vector2& inPosition)
{
	position = inPosition;
}

void Card::draw()
{
	Rectangle rec{ position.x, position.y, CARD_SIZE.x, CARD_SIZE.y };
	DrawRectangleRounded(rec, 0.2, 4, getCardColor());

	auto ptr = model.lock();
	if (ptr)
	{
		const bool isTextVisible = ptr->getIsFlipped() || ptr->getIsMatched();
		if (isTextVisible) {
			DrawText(ptr->getText().c_str(), position.x + 10, position.y + 10, 20, MAROON);
		}
	}	
}

Color Card::getCardColor() const
{
	auto ptr = model.lock();
	if (ptr && ptr->getIsFlipped()) {
		return SKYBLUE;
	}
	return DARKBLUE;
}

Rectangle Card::getBoundsRect() const
{
	return { .x = position.x, .y = position.y, .width = CARD_SIZE.x, .height = CARD_SIZE.y };
}

void Card::update()
{
	for (auto& x : components) {
		x->update();
	}
}