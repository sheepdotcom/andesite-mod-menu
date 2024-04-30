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

void Client::Setup() {
	SetupUniversal();
}

void Client::SetupUniversal() {
	Hacks* universal = new Universal();
	universal->name = "Universal";
	universal->id = "universal-section";

	universal->hacks.push_back(new Hack("Testig", "testing", "I am testing the massive update!"));
	universal->hacks.push_back(new Hack("Hello", "hello", "This is a hello test."));
	universal->hacks.push_back(new Hack("Long Word Test", "longwordtest", "This is a test for long phrases or sentences because I need to test if <cg>everything</c> works fine"));
	universal->hacks.push_back(new Hack("Options Test", "optionstest", "Testing Custom Options!"));

	Client::instance->sections.push_back(universal);

	Client::GetHack("optionstest")->options.push_back(new Hack("Hello", "optionstest-hello"));
	Client::GetHack("optionstest")->options.push_back(new Hack("Hi", "optionstest-hi"));
}