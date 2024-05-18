#include "Card.h"
#include "models/CardModel.h"

namespace {
	Vector2 CARD_SIZE{ .x = 100, .y = 150 };
}

void Card::setPosition(const Vector2& inPosition)
{
	position = inPosition;
}

void Card::setModel(const std::shared_ptr<CardModel>& inModel) 
{
	model = inModel;
}

void Card::draw()
{
	Rectangle rec{ position.x, position.y, CARD_SIZE.x, CARD_SIZE.y };
	DrawRectangleRounded(rec, 0.2, 4, DARKBLUE);
	if (model)
	{
		DrawText(model->getText().c_str(), position.x + 10, position.y + 10, 20, MAROON);
	}	
}
