#include "menu.hpp"

using namespace geode::prelude;

void AndesiteMenu::useless(CCObject* p0) {
	//Useless, just for testing
}

void AndesiteMenu::addHackToMenu(CCPoint pos) {
	//todo: input hack into function (like prism menu)
	//todo: move this code somewhere else and improve it
	auto toggle = CCMenuItemToggler::create(
		ButtonSprite::create("Useless", 112.f, true, "bigFont.fnt", "GJ_button_05.png", 30, 1.f),
		ButtonSprite::create("Useless", 112.f, true, "bigFont.fnt", "GJ_button_01.png", 30, 1.f),
		m_content,
		menu_selector(AndesiteMenu::useless)
	);
	toggle->setUserData(this);
	toggle->toggle(false);
	toggle->setPosition(pos);
	toggle->setZOrder(2);
	toggle->setID("useless-toggle");

	m_content->addChild(toggle);
}

bool AndesiteMenu::init() {
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	if (!this->initWithColor({0,0,0,105})) return false;

	//Background
	this->m_mainLayer = CCLayer::create();
	this->addChild(m_mainLayer);
	auto bg = CCScale9Sprite::create("GJ_square02.png", {0.f,0.f,80.f,80.f});
	bg->setContentSize({450.f,300.f});
	bg->setPosition(winSize.width/2,winSize.height/2);
	bg->setID("menu-bg");
	m_mainLayer->addChild(bg);

	//Close Button
	this->m_buttonMenu = CCMenu::create();
	m_buttonMenu->setID("close-menu");
	m_mainLayer->addChild(m_buttonMenu);
	auto closeBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"), this, menu_selector(AndesiteMenu::onClose));
	closeBtn->setPosition(ccp((-450.f+26.f)/2,(300.f-26.75f)/2));
	closeBtn->setID("close-button");
	m_buttonMenu->addChild(closeBtn);

	//Title Text
	auto title = CCLabelBMFont::create("Andesite", "bigFont.fnt");
	title->setPosition(ccp(450.f/2,300.f-25.f));
	title->setID("menu-title");
	auto separator = CCSprite::createWithSpriteFrameName("floorLine_001.png");
	separator->setScaleX(0.5f);
	separator->setScaleY(1.f);
	separator->setPosition(ccp(450.f/2,300.f-45.f));
	separator->setOpacity(51);
	separator->setID("menu-seperator");
	bg->addChild(title);
	bg->addChild(separator);

	//Scroll Layer Background
	auto scrollBG = CCScale9Sprite::create("square02_001.png", {0.f,0.f,80.f,80.f});
	scrollBG->setContentSize({300.f,230.f});
	scrollBG->setPosition(ccp(290.f,125.f));
	scrollBG->setOpacity(100.f);
	scrollBG->setID("hacks-bg");
	bg->addChild(scrollBG);

	//Scroll Layer
	m_scrollLayer = ScrollLayer::create({320.f,230.f});
	m_content = CCMenu::create();
	m_content->registerWithTouchDispatcher();
	m_content->setPosition(m_scrollLayer->getPosition());
	m_content->setContentSize(m_scrollLayer->getContentSize());
	m_content->setID("hacks-menu");
	m_scrollLayer->m_contentLayer->addChild(m_content);
	m_scrollLayer->setTouchEnabled(true);
	scrollBG->addChild(m_scrollLayer);

	for (size_t i = 0; i < 1; i++) {
		AndesiteMenu::addHackToMenu(ccp(70.f, m_content->getContentHeight() - 20 - (30 * i)));
	}

	m_scrollLayer->moveToTop();
	m_scrollLayer->enableScrollWheel();

	this->registerWithTouchDispatcher();
	cocos::handleTouchPriority(this);
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