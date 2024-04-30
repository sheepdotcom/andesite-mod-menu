#pragma once

using namespace geode::prelude;

//Were taking the QOLMod approach with this one (I never copy+paste code, I always write it myself, but that doesn't mean I won't use it as a guide).
class Hack {
public:
	std::string name;
	std::string id;
	std::string desc;
	bool enabled = false;
	std::vector<Hack*> options = {};

	Hack(std::string hName, std::string hId, std::string hDesc = "") {
		name = hName;
		id = hId;
		desc = hDesc;
		enabled = Mod::get()->getSavedValue<bool>(id+"_enabled", enabled);
		Mod::get()->setSavedValue<bool>(id + "_enabled", enabled);
	}

	void onToggle(CCObject* p0);
	void onInfo(CCObject* p0);
	void onOptions(CCObject* p0);
	void addHackToMenu(Hack* hack, CCMenu* menu, CCPoint pos);
};

//Yes, Hacks and Hack, I know but Hacks sounds better for some scenarios, even though I probably shouldn't worry about how they sound to a user.
//Also yes, multiple things for each section of hacks, but it's just so much easier to do it this way.
class Hacks {
public:
	std::string name;
	std::string id;
	std::vector<Hack*> hacks;
};

//Here we go, time to use QOLMod's method of making multiple classes for each section, though its a pretty good idea.
class Universal : public Hacks {
public:

};