#pragma once
#include "raylib.h"
#include <memory>

class CardModel;

class Card {
public:
	void setPosition(const Vector2& inPosition);
	void setModel(const std::shared_ptr<CardModel>& inModel);
	void draw();

private:
	Vector2 position = { .x = 0, .y = 0 };
	std::shared_ptr<CardModel> model;
};