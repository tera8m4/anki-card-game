#include "models/CardModel.h"

CardModel::CardModel(const std::string& inText) : text{inText}
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

void CardModel::setIsFlipped(const bool bInValue)
{
	bIsFlipped = bInValue;
}

void CardModel::setIsMatched(const bool bInValue)
{
	bIsMatched = bInValue;
}

void CardModel::setText(const std::string& inNewText)
{
	text = inNewText;
}

