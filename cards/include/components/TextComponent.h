#pragma once

#include <string>
#include <memory>
#include "SceneComponent.h"

struct Font;
class Card;

class TextComponent : public SceneComponent
{
public:
	using SceneComponent::SceneComponent;

	void setText(const std::string& inText);
	void setPosition(const float inX, const float inY);
	virtual void draw() override;
	virtual void update() override;

private:
	std::string text;
	std::unique_ptr<Font> font;
	float x = 0;
	float y = 0;

	std::unique_ptr<Font> GenerateFont() const;
};