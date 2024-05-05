#include "Hacks.hpp"
#include "../UI/HackOptionsMenu.hpp"
#include "../UI/HackMenu.hpp"
#include "../UI/Dropdown.hpp"

using namespace geode::prelude;

void Hack::onToggle(CCObject* p0) {
	auto hack = static_cast<Hack*>(static_cast<CCNode*>(p0)->getUserData());

	hack->enabled = !hack->enabled;
	Mod::get()->setSavedValue(hack->id + "_enabled", hack->enabled);
}

void Hack::onInfo(CCObject* p0) {
	auto hack = static_cast<Hack*>(static_cast<CCNode*>(p0)->getUserData());

	FLAlertLayer::create(hack->name.c_str(), hack->desc.c_str(), "OK")->show();
}

void Hack::onOptions(CCObject* p0) {
	auto hack = static_cast<Hack*>(static_cast<CCNode*>(p0)->getUserData());

	auto ret = HackOptionsMenu::create(hack);
	CCScene::get()->addChild(ret, 3000);
}

void Hack::addHackToMenu(Hack* hack, CCMenu* menu, CCPoint pos) {
	//This may be stupid but I just like it this way, much easier to work with.
	auto name = hack->name;
	auto id = hack->id;
	auto desc = hack->desc;
	auto enabled = hack->enabled;
	auto options = hack->options;

	auto toggle = CCMenuItemToggler::create(
		ButtonSprite::create(name.c_str(), 100.f, true, "bigFont.fnt", "GJ_button_05.png", 30, 0.8f),
		ButtonSprite::create(name.c_str(), 100.f, true, "bigFont.fnt", "GJ_button_01.png", 30, 0.8f),
		menu,
		menu_selector(Hack::onToggle)
	);
	toggle->toggle(enabled);
	toggle->setPosition(pos);
	toggle->setZOrder(2);
	toggle->setUserData(this);
	toggle->setID(id + "-toggle");

	if (desc.size() != 0 && options.size() == 0) {
		auto info = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"),
			menu,
			menu_selector(Hack::onInfo)
		);
		info->m_baseScale = 0.85f;
		info->setScale(info->m_baseScale);
		info->setPosition(pos + ccp(75.f, 0.f));
		info->setContentSize(info->getContentSize() * 1.5f);
		static_cast<CCSprite*>(info->getChildren()->objectAtIndex(0))->setPosition(info->getContentSize() / 2);
		info->setUserData(this);
		info->setID(id + "-info");

		menu->addChild(info);
	}

	if (options.size() != 0) {
		auto optionsBtn = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_plus3Btn_001.png"),
			menu,
			menu_selector(Hack::onOptions)
		);
		optionsBtn->setPosition(pos + ccp(75.f, 0.f));
		optionsBtn->setUserData(this);
		optionsBtn->setID(id + "-options");
		
		menu->addChild(optionsBtn);
	}

	menu->addChild(toggle);
}

void InputHack::addHackToMenu(Hack* hack, CCMenu* menu, CCPoint pos) {
	InputHack* inputHack = static_cast<InputHack*>(hack);

	auto input = TextInput::create(100.f, inputHack->placeholder.c_str());
	input->getInputNode()->setAllowedChars(inputHack->allowedCharacters);
	input->setPosition(pos);
	input->setDelegate(this);
	auto inputLimiter = (input->getContentWidth() - 10.f) / std::max(input->getInputNode()->m_placeholderLabel->getContentWidth(), (input->getContentWidth() - 10.f));
	input->getInputNode()->setLabelPlaceholderScale(inputLimiter);
	input->setString(inputHack->text);
	input->setID(inputHack->id);

	auto label = CCLabelBMFont::create(inputHack->name.c_str(), "bigFont.fnt");
	label->setScale(0.3f);
	label->setOpacity(125);
	label->setPosition(ccp(0.f, input->getContentHeight() + 0.f));
	label->setAnchorPoint(ccp(0.f, 0.5f));
	label->setID("input-label");
	input->addChild(label);

	if (inputHack->suffix.size() != 0) {
		auto suffix = CCLabelBMFont::create(inputHack->suffix.c_str(), "bigFont.fnt");
		suffix->setScale(0.3f);
		suffix->setOpacity(125);
		suffix->setPosition(ccp(input->getContentWidth(), input->getContentHeight() / 2));
		suffix->setID("input-suffix");
		input->addChild(suffix);
	}

	menu->addChild(input);

	this->inputField = input;
}

void InputHack::textChanged(CCTextInputNode* p0) {
	//Custom character filter so people with other hacks cant text bypass hopefully.
	std::string tempText = p0->getString();
	text = "";
	for (int i = 0; i < tempText.size(); i++) {
		char l = tempText[i];
		if (allowedCharacters.find(l) != std::string::npos) {
			text.push_back(l);
		}
	}
	static_cast<TextInput*>(p0->getParent())->setString(text); //Me when static_cast
	Mod::get()->setSavedValue<std::string>(id + "_value", text);
}

void DropdownHack::addHackToMenu(Hack* hack, CCMenu* menu, CCPoint pos) {
	auto dropHack = static_cast<DropdownHack*>(hack);

	auto dropdown = Dropdown::create(ccp(100, 30), dropHack->content, menu_selector(DropdownHack::onDropdownSelectionChanged), dropHack->index);
	dropdown->setUserData(this);
	dropdown->setPosition(pos - (dropdown->getContentSize() / 2));
	dropdown->setID(dropHack->id);

	menu->addChild(dropdown);
}

void DropdownHack::onDropdownSelectionChanged(CCObject* p0) {
	auto hack = static_cast<DropdownHack*>(static_cast<CCNode*>(p0)->getParent()->getUserData());
	auto drop = static_cast<Dropdown*>(static_cast<CCNode*>(p0)->getParent());

	hack->index = drop->selected;
	Mod::get()->setSavedValue<int>(hack->id + "_index", hack->index);
}

void Hacks::addSectionToMenu(Hacks* section, CCMenu* menu, CCPoint pos) {
	auto name = section->name;
	auto id = section->id;

	//String streams are cool
	std::stringstream buttonType;
	//buttonType << "GJ_button_0" << (HackMenu::currentSection->id == id ? 2 : 1) << ".png";
	buttonType << "GJ_longBtn0" << (HackMenu::currentSection->id == id ? 2 : 1) << "_001.png";

	//Add menu selector
	auto sectionBtn = CCMenuItemSpriteExtra::create(
		//ButtonSprite::create(name.c_str(), 69.f, true, "bigFont.fnt", buttonType.str().c_str(), 30, 0.8f),
		CCSprite::createWithSpriteFrameName(buttonType.str().c_str()),
		menu,
		menu_selector(Hacks::onSectionClicked)
	);
	sectionBtn->setPosition(pos);
	sectionBtn->m_baseScale = 90.f / sectionBtn->getContentWidth(); //Math to get the width to be 90 instead of 91.75
	sectionBtn->setScale(sectionBtn->m_baseScale);
	sectionBtn->setZOrder(3);
	sectionBtn->setUserData(this);
	sectionBtn->setID(id+"-section");

	//Manually add CCLabelBMFont
	auto sectionLabel = CCLabelBMFont::create(name.c_str(), "bigFont.fnt");
	sectionLabel->setPosition((sectionBtn->getContentSize() / 2) + ccp(0.f, 1.5f));
	auto labelLimiter = (90.f - 10.f) / std::max(sectionLabel->getContentWidth(), (90.f - 10.f));
	sectionLabel->setScale(labelLimiter);
	sectionLabel->setZOrder(4);
	sectionBtn->addChild(sectionLabel);

	menu->addChild(sectionBtn);
}

void Hacks::onSectionClicked(CCObject* p0) {
	auto section = static_cast<Hacks*>(static_cast<CCNode*>(p0)->getUserData());
	auto sectionMenu = static_cast<CCMenu*>(static_cast<CCNode*>(p0)->getParent());

	auto menu = static_cast<HackMenu*>(CCScene::get()->getChildByID("andesite-menu"));

	HackMenu::currentSection = section;
	sectionMenu->removeAllChildrenWithCleanup(true);

	for (size_t s = 0; s < Client::instance->sections.size(); s++) {
		Client::instance->sections[s]->addSectionToMenu(
			Client::instance->sections[s],
			sectionMenu,
			ccp(50.f, 210.f - (35 * s))
		);
	}

	menu->regenSection(section);
}