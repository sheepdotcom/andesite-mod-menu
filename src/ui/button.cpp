#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "menu.hpp"
#include "button.hpp"

using namespace geode::prelude;

void AndesiteButton::onButtonClicked(CCObject* p0) {
	AndesiteMenu::create()->show();
}

class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;

		auto menu = CCMenu::create();
		menu->setPosition({0,0});
		menu->setContentSize({0,0});
		this->addChild(menu);
		auto andesiteSpr = CCSprite::createWithSpriteFrameName("GJ_plainBtn_001.png");
		auto andesiteBtn = CCMenuItemSpriteExtra::create(andesiteSpr, this, menu_selector(AndesiteButton::onButtonClicked));
		andesiteBtn->setID("andesite-button");
		andesiteBtn->setPosition({47,210});
		menu->addChild(andesiteBtn);

		return true;
	}
};