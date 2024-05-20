#include "models/CardModel.h"

CardModel::CardModel(const std::string& inText, const std::string& inKey, const std::string& inMatchingKey) : text{inText}, key{inKey}, matchingKey{inMatchingKey}
{

}

bool CardModel::getIsFlipped() const
{
	return bIsFlipped;
}

bool CardModel::getIsMatched() const
{
	return bIsMatched;
}

const std::string& CardModel::getText() const 
{
	return text;
}

const std::string& CardModel::getKey() const
{
    return key;
}

const std::string& CardModel::getMatchingKey() const
{
    return matchingKey;
}

void CardModel::setIsFlipped(const bool bInValue)
{
	bIsFlipped = bInValue;
}

void CardModel::setIsMatched(const bool bInValue)
{
	bIsMatched = bInValue;
}
