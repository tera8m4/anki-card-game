#include "ResourceManager.h"
#include "raylib.h"

ResourceManager& ResourceManager::getInstance()
{
	static ResourceManager instance;

	return instance;
}

void ResourceManager::loadFont(const std::string& inName, const std::filesystem::path& inPath)
{
	fonts[inName] = LoadFontEx("resources/pixantiqua.ttf", 32, nullptr, 250);
}

Font ResourceManager::getFont(const std::string& inName)
{
	return fonts[inName];
}
