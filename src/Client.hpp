#pragma once

#include "Hacks/Hacks.hpp"

using namespace geode::prelude;

//Sorry QOLMod
class Client {
public:
	static inline Client* instance = nullptr;

	std::vector<Hacks*> sections;

	static Hack* GetHack(std::string id);
	static void Setup();
	static void SetupUniversal();
};