#include "Client.hpp"

using namespace geode::prelude;

//Sorry again QOLMod
Hack* Client::GetHack(std::string id) {
	if (!instance) return nullptr;
	for (size_t s = 0; s < instance->sections.size(); s++) {
		for (size_t h = 0; h < instance->sections[s]->hacks.size(); h++) {
			if (!instance->sections[s]->hacks[h]->id.compare(id)) {
				return instance->sections[s]->hacks[h];
			}
		}
	}
	return nullptr;
}

Hacks* Client::GetSection(std::string id) {
	if (!instance) return nullptr;
	for (size_t s = 0; s < instance->sections.size(); s++) {
		if (!instance->sections[s]->id.compare(id)) {
			return instance->sections[s];
		}
	}
	return nullptr;
}

//Useless for now
Hacks* Client::GetSectionOfHack(std::string id) {
	if (!instance) return nullptr;
	for (size_t s = 0; s < instance->sections.size(); s++) {
		for (size_t h = 0; h < instance->sections[s]->hacks.size(); h++) {
			if (!instance->sections[s]->id.compare(id)) {
				return instance->sections[s];
			}
		}
	}
	return nullptr;
}

bool Client::HackEnabled(std::string id) {
	if (auto hack = Client::GetHack(id)) {
		return hack->enabled;
	}
	return false;
}

void Client::Setup() {
	SetupUniversal();
	SetupCreator();
}

void Client::SetupUniversal() {
	Hacks* universal = new Universal();
	universal->name = "Universal";
	universal->id = "universal";

	Client::instance->sections.push_back(universal);
}

void Client::SetupCreator() {
	Hacks* creator = new Creator();
	creator->name = "Creator";
	creator->id = "creator";

	creator->hacks.push_back(new Hack("Copy Hack", "copy-hack", "Copy any online level."));

	Client::instance->sections.push_back(creator);
}

void Client::SetupCosmetic() {
	Hacks* cosmetic = new Cosmetic();
	cosmetic->name = "Cosmetic";
	cosmetic->id = "cosmetic";

	Client::instance->sections.push_back(cosmetic);
}