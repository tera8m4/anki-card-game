#pragma once

#include <string>

class CardModel {
public:
	explicit CardModel(const std::string& inText);

	bool getIsFlipped() const;
	bool getIsMatched() const;
	const std::string& getText() const;

	void setIsFlipped(const bool bInValue);
	void setIsMatched(const bool bInValue);
	void setText(const std::string& inNewText);

private:
	bool bIsFlipped = false;
	bool bIsMatched = false;
	std::string text;
};