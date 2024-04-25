#include "menu.hpp"

using namespace geode::prelude;

void AndesiteMenu::useless(CCObject* p0) {
	//Useless, just for testing
}

void AndesiteMenu::addHackToMenu(CCNode* menu) {
	//todo: input hack into function (like prism menu)
	//todo: move this code somewhere else and improve it
	auto toggle = CCMenuItemToggler::createWithStandardSprites(menu, menu_selector(AndesiteMenu::useless), 0.75f);
	toggle->setUserData(this);
	toggle->setID("useless-toggle");
	toggle->setPosition({20.f,210.f});

	auto name = CCLabelBMFont::create("Useless", "bigFont.fnt");
	name->setAnchorPoint(ccp(0.f,0.5f));
	name->setPosition(ccp(20.f,210.f) + ccp(15.f,0.f));
	name->setScale(0.6f);
	name->limitLabelWidth(110, 0.6f, 0.1f);

	menu->addChild(toggle);
	menu->addChild(name);
}

bool AndesiteMenu::init() {
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	if (!this->initWithColor({0,0,0,105})) return false;

	this->m_mainLayer = CCLayer::create();
	this->addChild(m_mainLayer);
	auto bg = CCScale9Sprite::create("GJ_square02.png", {0.f,0.f,80.f,80.f});
	bg->setContentSize({450.f,300.f});
	bg->setPosition(winSize.width/2,winSize.height/2);
	m_mainLayer->addChild(bg);

	this->m_buttonMenu = CCMenu::create();
	m_mainLayer->addChild(m_buttonMenu);
	auto closeBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"), this, menu_selector(AndesiteMenu::onClose));
	closeBtn->setPosition(ccp((-450.f+26.f)/2,(300.f-26.75f)/2));
	m_buttonMenu->addChild(closeBtn);

	auto scrollBG = CCScale9Sprite::create("square02_001.png", {0.f,0.f,80.f,80.f});
	scrollBG->setContentSize({300.f,230.f});
	scrollBG->setPosition(ccp(290.f,125.f));
	scrollBG->setOpacity(100.f);
	bg->addChild(scrollBG);

	auto scrollLayer = ScrollLayer::create({320.f,230.f});
	auto content = CCMenu::create();
	content->registerWithTouchDispatcher();
	scrollLayer->m_contentLayer->addChild(content);
	scrollLayer->setTouchEnabled(true);
	scrollBG->addChild(scrollLayer);

	AndesiteMenu::addHackToMenu(scrollLayer->m_contentLayer);

	scrollLayer->moveToTop();
	scrollLayer->enableScrollWheel();

	this->registerWithTouchDispatcher();
	handleTouchPriority(this);
	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);
	this->setMouseEnabled(true);
	this->setID("andesite-menu");

	return true;
}

void AndesiteMenu::onClose(CCObject* p0) {
	this->removeFromParentAndCleanup(true);
}

AndesiteMenu* AndesiteMenu::create() {
	auto ret = new AndesiteMenu();
	if (ret && ret->init()) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
};