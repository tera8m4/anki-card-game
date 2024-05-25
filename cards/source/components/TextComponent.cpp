#include "components/TextComponent.h"
#include <raylib.h>
#include <spdlog/spdlog.h>

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

    spdlog::info("text: {} codepoints: {}", text, codepointCount);

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

void TextComponent::setWrapAt(const int inWrapAt) {
    wrapAt = inWrapAt;
}

void TextComponent::draw()
{
	if (bIsVisible && text.length() > 0) {
        if (wrapAt > 0)
        {
            std::string wrappedText;
            int lastSpace = 0;
            for (int i = 0; i < text.size(); ++i) {
                const char c = text[i];
                wrappedText.push_back(c);

                auto vec = MeasureTextEx(*font.get(), wrappedText.c_str(), 32, 2);
                if (c == ' ') {
                    lastSpace = i;
                }
                if (vec.x > wrapAt && lastSpace > 0) {
                    wrappedText[lastSpace] = '\n';
                    lastSpace = 0;
                }
            }
            DrawTextEx(*font.get(), wrappedText.c_str(), Vector2{ x, y }, 32, 2, LIME);
        }
        else
        {
            DrawTextEx(*font.get(), text.c_str(), Vector2{ x, y }, 32, 2, LIME);
        }
        
	}
}
