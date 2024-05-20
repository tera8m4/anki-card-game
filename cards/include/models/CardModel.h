#pragma once

#include <string>

class CardModel {
public:
	explicit CardModel(const std::string& inText, const std::string& inKey, const std::string& inMatchingKey);

	bool getIsFlipped() const;
	bool getIsMatched() const;
	const std::string& getText() const;
    const std::string& getKey() const;
    const std::string& getMatchingKey() const;

	void setIsFlipped(const bool bInValue);
	void setIsMatched(const bool bInValue);

private:
	bool bIsFlipped = false;
	bool bIsMatched = false;
    std::string text;
    std::string key;
    std::string matchingKey;
};
