#include "components/BaseButtonComponent.h"
#include <raylib.h>
#include "Card.h"

BaseButtonComponent::~BaseButtonComponent() {}

void BaseButtonComponent::update()
{
	const Vector2& mousePoint = GetMousePosition();
	bool isNowPressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePoint, getOwner()->getBoundsRect());

	if (bIsPressed != isNowPressed)
	{
		bIsPressed = isNowPressed;

		if (!isNowPressed) {
			onClicked();
		}
	}
}

void BaseButtonComponent::onClicked()
{
	if (onClickedCallback)
	{
		onClickedCallback(this);
	}
}
