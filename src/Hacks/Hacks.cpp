#include "Hacks.hpp"
#include "../UI/HackOptionsMenu.hpp"
#include "../UI/HackMenu.hpp"

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

void Hacks::addSectionToMenu(Hacks* section, CCMenu* menu, CCPoint pos) {
	auto name = section->name;
	auto id = section->id;

	//String streams are cool
	std::stringstream buttonType;
	buttonType << "GJ_button_0" << (HackMenu::currentSection->id == id ? 2 : 1) << ".png";

	//Add menu selector
	auto sectionBtn = CCMenuItemSpriteExtra::create(
		ButtonSprite::create(name.c_str(), 69.f, true, "bigFont.fnt", buttonType.str().c_str(), 30, 0.8f),
		menu,
		menu_selector(Hacks::onSectionClicked)
	);
	sectionBtn->setPosition(pos);
	sectionBtn->setZOrder(3);
	sectionBtn->setUserData(this);
	sectionBtn->setID(id+"-section");

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