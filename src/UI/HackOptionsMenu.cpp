#include "HackOptionsMenu.hpp"

using namespace geode::prelude;

void HackOptionsMenu::onClose(CCObject* p0) {
	this->removeFromParent();
}

bool HackOptionsMenu::init(Hack* hack, float mWidth, float mHeight) {
	if (!CCLayerColor::init()) return false;

	currentHack = hack;

	auto menu = CCMenu::create();
	menu->setContentSize(ccp(mWidth,mHeight));
	menu->setPosition(ccp(0,0));
	menu->setTouchPriority(-499);
	menu->setID("menu");

	auto bg = CCScale9Sprite::create("GJ_square04.png");
	bg->setContentSize(menu->getContentSize());
	bg->setPosition(CCDirector::get()->getWinSize()/2);
	bg->setID("options-bg");
	bg->addChild(menu);

	this->addChild(bg);

	auto title = CCLabelBMFont::create(hack->name.c_str(), "bigFont.fnt");
	title->setPosition(ccp(menu->getContentWidth()/2,menu->getContentHeight()-20));
	title->setScale(1.f);
	title->setID("menu-title");
	menu->addChild(title);

	auto desc = CCLabelBMFont::create(hack->desc.c_str(), "goldFont.fnt");
	desc->setPosition(ccp(menu->getContentWidth()/2,menu->getContentHeight()-50));
	desc->setScale(0.75f);
	desc->setID("menu-description");
	menu->addChild(desc);

	auto closeBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"), this, menu_selector(HackOptionsMenu::onClose));
	closeBtn->setPosition(ccp(0,mHeight));
	closeBtn->setID("close-button");
	menu->addChild(closeBtn);

	for (size_t i = 0; i < hack->options.size(); i++) {
		auto option = hack->options[i];
		
		option->addHackToMenu(option, menu, ccp(80+(140*(i%2)), 35));
	}
	
	handleTouchPriority(this);
	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);
	this->setMouseEnabled(true);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -502, true);

	this->setID("options-menu");

	return true;
}

HackOptionsMenu* HackOptionsMenu::create(Hack* hack) {
	HackOptionsMenu* ret = new HackOptionsMenu();
	if (ret && ret->init(hack, 300.f, 135.f)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}