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
}

void Client::Setup() {
	SetupUniversal();
	SetupCreator();
}

void Client::SetupUniversal() {
	Hacks* universal = new Universal();
	universal->name = "Universal";
	universal->id = "universal";

	universal->hacks.push_back(new Hack("Testig", "testing", "I am testing the massive update!"));
	universal->hacks.push_back(new Hack("Hello", "hello", "This is a hello test."));
	universal->hacks.push_back(new Hack("Long Word Test", "longwordtest", "This is a test for long phrases or sentences because I need to test if <cg>everything</c> works fine"));
	universal->hacks.push_back(new Hack("Options Test", "optionstest", "Testing Custom Options!"));
	universal->hacks.push_back(new Hack("Super Duper Long Options Hack Name And Description Test", "superduperlongoptionshacknameanddescriptiontest", "This is a test for ultra long options name and description testing."));

	Client::instance->sections.push_back(universal);

	Client::GetHack("optionstest")->options.push_back(new Hack("Hello", "optionstest-hello"));
	Client::GetHack("optionstest")->options.push_back(new Hack("Hi", "optionstest-hi"));

	Client::GetHack("superduperlongoptionshacknameanddescriptiontest")->options.push_back(new Hack("You like these tests dont you?", "superduperlongoptionshacknameanddescriptiontest-youlikethesetestsdontyou"));
	Client::GetHack("superduperlongoptionshacknameanddescriptiontest")->options.push_back(new Hack("Because I do.", "superduperlongoptionshacknameanddescriptiontest-becauseido"));
	Client::GetHack("superduperlongoptionshacknameanddescriptiontest")->options.push_back(new Hack("Especially when you get to put funny names for your hacks.", "superduperlongoptionshacknameanddescriptiontest-especiallywhenyougettoputfunnynamesforyourhacks"));
}

void Client::SetupCreator() {
	Hacks* creator = new Creator();
	creator->name = "Creator";
	creator->id = "creator";

	creator->hacks.push_back(new Hack("New Section!", "newsection", "Welcome to the new section!"));

	Client::instance->sections.push_back(creator);

	Client::GetHack("newsection")->options.push_back(new InputHack("Input Test", "newsection-inputtest", "", "x"));
	Client::GetHack("newsection")->options.push_back(new DropdownHack("Dropdown Test", "newsection-dropdowntest", {"one test", "two test", "red test", "blue test"}));
}