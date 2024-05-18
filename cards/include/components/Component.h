#pragma once

class Card;

class Component {
public:
	explicit Component(Card* inOwner) : owner{ inOwner } {};
	Component() = delete;
	virtual ~Component() = 0 {}
	Card* getOwner() const { return owner; }
	virtual void update() = 0 {}

private:
	Card* owner;
};