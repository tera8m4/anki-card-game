#include "Card.h"
#include "models/CardModel.h"
#include "components/BaseButtonComponent.h"
#include "ResourceManager.h"
#include "components/TextComponent.h"


namespace {
	Vector2 CARD_SIZE{ .x = 100, .y = 150 };
}

Card::Card()
{
	components.push_back(std::make_shared<BaseButtonComponent>(this));
	textComponent = std::make_shared<TextComponent>(this);
	components.push_back(textComponent);

	sceneComponents.push_back(textComponent);
}


void Card::setModel(const std::shared_ptr<CardModel>& inModel)
{
	model = inModel;

	textComponent->setText(inModel->getText());
}

void Card::setPosition(const Vector2& inPosition)
{
	position = inPosition;
	
	textComponent->setPosition(position.x + 20, position.y + 20);
}

void Card::draw()
{
	Rectangle rec{ position.x, position.y, CARD_SIZE.x, CARD_SIZE.y };
	DrawRectangleRounded(rec, 0.2, 4, getCardColor());

	for (auto& x : sceneComponents) {
		x->draw();
	}
}

Color Card::getCardColor() const
{
    auto ptr = model.lock();
    if (!ptr)
    {
        return DARKBLUE;
    }
    if (ptr->getIsMatched()) {
        return DARKPURPLE;
    }
    if (ptr->getIsFlipped()) {
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

    auto ptr = model.lock();
    textComponent->setVisibility(ptr && (ptr->getIsFlipped() || ptr->getIsMatched()));
}
