#pragma once

#include "Hacks/Hacks.hpp"

using namespace geode::prelude;

//Sorry QOLMod
class Client {
public:
	static inline Client* instance = nullptr;

	std::vector<Hacks*> sections;

	static Hack* GetHack(std::string id);
	static Hacks* GetSection(std::string id);
	static Hacks* GetSectionOfHack(std::string id);

	static bool HackEnabled(std::string id);

	static void Setup();
	static void SetupUniversal();
	static void SetupCreator();
	static void SetupCosmetic();
};