#pragma once
#include "Component.h"
#include <functional>

class BaseButtonComponent : public Component {
public:
	BaseButtonComponent(Card* card) : Component(card) {}
	virtual ~BaseButtonComponent();
	virtual void update() override;
	std::function<void(BaseButtonComponent*)> onClickedCallback;

private:
	bool bIsPressed = false;

	void onClicked();	
};