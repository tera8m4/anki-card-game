#pragma once

#include <string>
#include <filesystem>
#include <raylib.h>
#include <unordered_map>

class ResourceManager
{
public:
	static ResourceManager& getInstance();
	void loadFont(const std::string& inName, const std::filesystem::path& inPath);
	Font getFont(const std::string& inName);


private:
	ResourceManager() = default;

	std::unordered_map<std::string, Font> fonts;
};