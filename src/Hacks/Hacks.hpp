#pragma once

#include <Geode/ui/TextInput.hpp>

using namespace geode::prelude;

//Were taking the QOLMod approach with this one (I never copy+paste code, I always write it myself, but that doesn't mean I won't use it as a guide).
class Hack {
public:
	std::string name;
	std::string id;
	std::string desc;
	bool enabled = false;
	bool def = false;
	std::vector<Hack*> options = {};

	Hack() {}
	/**
		Creates a new hack. Remember to not use color codes, especially since it doesn't work with any hack that has options.
		@param hName Name of the hack
		@param hId ID of the hack. The id is what is refered to by almost everything so don't change it.
		@param hDesc Description of the hack. This is completely optional.
	*/
	Hack(std::string hName, std::string hId, std::string hDesc = "", bool hDefault = false) {
		name = hName;
		id = hId;
		desc = hDesc;
		def = hDefault;
		enabled = Mod::get()->getSavedValue<bool>(id + "_enabled", def);
		Mod::get()->setSavedValue<bool>(id + "_enabled", enabled);
	}

	void onToggle(CCObject* p0);
	void onInfo(CCObject* p0);
	void onOptions(CCObject* p0);
	virtual void addHackToMenu(Hack* hack, CCMenu* menu, CCPoint pos);
};

class InputHack : public Hack, public TextInputDelegate {
public:
	std::string text = "";
	std::string placeholder = "";
	std::string suffix = "";
	std::string allowedCharacters = "0123456789.";

	TextInput* inputField = nullptr;

	/**
		Creates a new input hack. Remember to not use color codes, especially since it doesn't work with any hack that has options.
		@param hName - Name of the hack
		@param hId - ID of the hack. The id is what is refered to by almost everything so don't change it.
		@param hDefault - Default value of the input hack. This is completely optional.
		@param hSuffix - Suffix text to display to the right of the input hack. This is completely optional.
		@param hPlaceholder - Placeholder text for when there is no text currently inputted. If left empty, then it will use the hack's name instead. This is completely optional.
		@param hCharacterFilter - A string containing only the allowed characters for the text field. This is completely optional.
	*/
	InputHack(std::string hName, std::string hId, std::string hDefault = "", std::string hSuffix = "", std::string hPlaceholder = "", std::string hCharacterFilter = "0123456789.") {
		name = hName;
		id = hId;
		suffix = hSuffix;
		placeholder = (hPlaceholder.size() != 0 ? hPlaceholder : hName);
		allowedCharacters = hCharacterFilter;
		text = Mod::get()->getSavedValue<std::string>(id + "_value", hDefault);
		Mod::get()->setSavedValue<std::string>(id + "_value", text);
	}

	void addHackToMenu(Hack* hack, CCMenu* menu, CCPoint pos);
	virtual void textChanged(CCTextInputNode* p0);
};

class DropdownHack : public Hack {
public:
	std::vector<std::string> content = {};
	int index = 0;

	DropdownHack(std::string hName, std::string hId, std::vector<std::string> hContent, int hDefault = 0) {
		name = hName;
		id = hId;
		content = hContent;
		index = Mod::get()->getSavedValue<int>(id + "_index", hDefault);
		Mod::get()->setSavedValue<int>(id + "_index", index);
	}

	void addHackToMenu(Hack* hack, CCMenu* menu, CCPoint pos);
	void onDropdownSelectionChanged(CCObject* p0);
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