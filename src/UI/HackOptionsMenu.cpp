#include "HackOptionsMenu.hpp"

using namespace geode::prelude;

void HackOptionsMenu::onClose(CCObject* p0) {
	this->removeFromParent();
}

void HackOptionsMenu::keyBackClicked() {
	HackOptionsMenu::onClose(nullptr);
}

bool HackOptionsMenu::init(Hack* hack, float mWidth, float mHeight) {
	if (!CCLayerColor::init()) return false;

	mHeight = mHeight + (40 * floor((hack->options.size() - 1) / 2));

	auto menu = CCMenu::create();
	menu->setContentSize(ccp(mWidth,mHeight));
	menu->setPosition(ccp(0,0));
	menu->setTouchPriority(-499);
	menu->setID("options-menu");

	auto bg = CCScale9Sprite::create("GJ_square04.png");
	bg->setContentSize(menu->getContentSize());
	bg->setPosition(CCDirector::get()->getWinSize() / 2);
	bg->setID("options-bg");
	bg->addChild(menu);

	this->addChild(bg);

	auto title = CCLabelBMFont::create(hack->name.c_str(), "bigFont.fnt");
	title->setPosition(ccp(menu->getContentWidth() / 2,menu->getContentHeight() - 20));
	float titleLimiter = (mWidth - 75) / (std::max(title->getContentWidth(), (mWidth - 75)));
	title->setScale(std::min(1.f, titleLimiter));
	title->setID("menu-title");
	menu->addChild(title);

	auto desc = CCLabelBMFont::create(hack->desc.c_str(), "goldFont.fnt");
	desc->setPosition(ccp(menu->getContentWidth() / 2,menu->getContentHeight() - 50));
	float descLimiter = (mWidth - 50) / (std::max(desc->getContentWidth(), (mWidth - 50)));
	desc->setScale(std::min(0.75f, descLimiter));
	desc->setID("menu-description");
	menu->addChild(desc);

	auto closeBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"), this, menu_selector(HackOptionsMenu::onClose));
	closeBtn->setPosition(ccp(11.5f, mHeight - 11.875f));
	closeBtn->setID("close-button");
	menu->addChild(closeBtn);

	for (size_t i = 0; i < hack->options.size(); i++) {
		auto option = hack->options[i];
		
		option->addHackToMenu(option, menu, ccp(80 + (140 * (i % 2)), 35 + (40 * floor((hack->options.size() - 1) / 2)) - (40 * floor(i / 2))));
	}
	
	handleTouchPriority(this);
	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);
	this->setMouseEnabled(true);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -502, true);

	this->setID("hack-options-menu");

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