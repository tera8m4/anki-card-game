#include "components/TextComponent.h"
#include <raylib.h>

namespace {
	static int* CodepointRemoveDuplicates(int* codepoints, int codepointCount, int* codepointsResultCount)
	{
		int codepointsNoDupsCount = codepointCount;
		int* codepointsNoDups = (int*)calloc(codepointCount, sizeof(int));
		memcpy(codepointsNoDups, codepoints, codepointCount * sizeof(int));

		// Remove duplicates
		for (int i = 0; i < codepointsNoDupsCount; i++)
		{
			for (int j = i + 1; j < codepointsNoDupsCount; j++)
			{
				if (codepointsNoDups[i] == codepointsNoDups[j])
				{
					for (int k = j; k < codepointsNoDupsCount; k++) codepointsNoDups[k] = codepointsNoDups[k + 1];

					codepointsNoDupsCount--;
					j--;
				}
			}
		}

		// NOTE: The size of codepointsNoDups is the same as original array but
		// only required positions are filled (codepointsNoDupsCount)

		*codepointsResultCount = codepointsNoDupsCount;
		return codepointsNoDups;
	}
}

void TextComponent::update()
{

}

std::unique_ptr<Font> TextComponent::GenerateFont() const
{
	// Get codepoints from text
	int codepointCount = 0;
	int* codepoints = LoadCodepoints(text.c_str(), &codepointCount);

	/*int codepointsNoDupsCount = 0;
	int* codepointsNoDups = CodepointRemoveDuplicates(codepoints, codepointCount, &codepointsNoDupsCount);
	UnloadCodepoints(codepoints);*/

	std::unique_ptr<Font> font = std::make_unique<Font>(LoadFontEx("assets/NotoSansJP-Regular.otf", 32, codepoints, codepointCount));

	free(codepoints);
	return font;
}

void TextComponent::setText(const std::string& inText)
{
	if (font)
	{
		UnloadFont(*font);
	}
	text = inText;

	font = GenerateFont();	
}

void TextComponent::setPosition(const float inX, const float inY)
{
	x = inX;
	y = inY;
}

void TextComponent::draw()
{
	if (text.length() > 0) {
		DrawTextEx(*font.get(), text.c_str(), Vector2{ x, y }, 32, 2, LIME);
	}
}
