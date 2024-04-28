#include "hacks.hpp"

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

void Hack::addHackToMenu(Hack* hack, CCMenu* menu, CCPoint pos) {
	//This may be stupid but I just like it this way, much easier to work with.
	auto name = hack->name;
	auto id = hack->id;
	auto desc = hack->desc;
	auto enabled = hack->enabled;

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

	menu->addChild(toggle);
	menu->addChild(info);
}