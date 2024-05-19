#pragma once
#include "raylib.h"
#include <memory>
#include <vector>
#include "components/Component.h"

class CardModel;
class SceneComponent;
class TextComponent;

class Card : public std::enable_shared_from_this<Card> {
public:
	Card();
	void setPosition(const Vector2& inPosition);
	void setModel(const std::shared_ptr<CardModel>& inModel);
	void draw();
	Rectangle getBoundsRect() const;
	void update();

	template<class T>
	T* findComponent() {
		for (const auto& x : components) {
			T* obj = dynamic_cast<T*>(x.get());
			if (obj != nullptr) {
				return obj;
			}
		}
		return nullptr;
	}

private:
	Vector2 position = { .x = 0, .y = 0 };
	std::weak_ptr<const CardModel> model;
	std::vector<std::shared_ptr<Component>> components;
	std::vector<std::shared_ptr<SceneComponent>> sceneComponents;
	std::shared_ptr<TextComponent> textComponent;

	Color getCardColor() const;
};