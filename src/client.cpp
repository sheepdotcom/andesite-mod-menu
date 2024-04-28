#include "client.hpp"

using namespace geode::prelude;

//Sorry again QOLMod
Hack* Client::GetHack(std::string id) {
	for (size_t s = 0; s < instance->sections.size(); s++) {
		for (size_t h = 0; h < instance->sections[s]->hacks.size(); h++) {
			if (!instance->sections[s]->hacks[h]->id.compare(id)) {
				return instance->sections[s]->hacks[h];
			}
		}
	}
	return nullptr;
}

void Client::Setup() {
	SetupUniversal();
}

void Client::SetupUniversal() {
	Hacks* universal = new Universal();
	universal->name = "Universal";
	universal->id = "universal-section";

	universal->hacks.push_back(new Hack("Testig", "testing", "I am testing the massive update!"));
	universal->hacks.push_back(new Hack("Hello", "hello", "This is a hello test."));

	Client::instance->sections.push_back(universal);
}