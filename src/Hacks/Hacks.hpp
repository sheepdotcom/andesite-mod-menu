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

	/**
		Creates a new hack. Remember to not use color codes, especially since it doesn't work with any hack that has options.
		@param hName Name of the hack
		@param hId ID of the hack. The id is what is refered to by almost everything so don't change it.
		@param hDesc Description of the hack. This is completely optional.
	*/
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

	void addSectionToMenu(Hacks* section, CCMenu* menu, CCPoint pos);
	void onSectionClicked(CCObject* p0);
};

//Here we go, time to use QOLMod's method of making multiple classes for each section, though its a pretty good idea.
class Universal : public Hacks {};
class Creator : public Hacks {};