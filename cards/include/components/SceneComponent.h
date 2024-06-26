#pragma once

#include "Component.h"

class SceneComponent : public Component {
public:
	using Component::Component;
	virtual void draw() = 0;
    virtual void setVisibility(const bool bInIsVisible) = 0;
};
