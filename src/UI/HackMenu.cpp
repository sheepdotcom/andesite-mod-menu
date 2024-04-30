#include "HackMenu.hpp"

using namespace geode::prelude;

void HackMenu::onOptions(CCObject* p0) {
	auto options = OptionsLayer::create();
	auto scene = CCDirector::sharedDirector()->getRunningScene();
	scene->addChild(options);
	options->setZOrder(512);
	options->showLayer(false);
}

bool HackMenu::init(float mWidth, float mHeight) {
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	if (!this->initWithColor({0,0,0,105})) return false;

	//Background
	auto mainLayer = CCLayer::create();
	this->addChild(mainLayer);
	auto bg = CCScale9Sprite::create("GJ_square02.png", {0.f,0.f,80.f,80.f});
	bg->setContentSize(ccp(mWidth, mHeight));
	bg->setPosition(winSize.width/2,winSize.height/2);
	bg->setID("menu-bg");
	mainLayer->addChild(bg);

	//Close Button
	auto buttonMenu = CCMenu::create();
	buttonMenu->setID("button-menu");
	mainLayer->addChild(buttonMenu);
	auto closeBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"), this, menu_selector(HackMenu::onClose));
	closeBtn->setPosition(ccp((-mWidth+26.f)/2,(mHeight-26.75f)/2));
	closeBtn->setID("close-button");
	buttonMenu->addChild(closeBtn);

	//Title Text
	auto title = CCLabelBMFont::create("Andesite Hacks", "bigFont.fnt");
	title->setPosition(ccp(mWidth/2,mHeight-25.f));
	title->setID("menu-title");
	auto separator = CCSprite::createWithSpriteFrameName("floorLine_001.png");
	separator->setScaleX(0.5f);
	separator->setScaleY(1.f);
	separator->setPosition(ccp(mWidth/2,mHeight-45.f));
	separator->setOpacity(51);
	separator->setID("menu-seperator");
	bg->addChild(title);
	bg->addChild(separator);

	//Settings Button
	auto settingsBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"), this, menu_selector(HackMenu::onOptions));
	settingsBtn->setPosition(ccp((mWidth/2)-30.f,(mHeight/2)-30.f));
	settingsBtn->m_baseScale = 0.8f;
	settingsBtn->setScale(settingsBtn->m_baseScale);
	settingsBtn->setID("settings-button");
	buttonMenu->addChild(settingsBtn);

	//Scroll Layer Background
	auto scrollBG = CCScale9Sprite::create("square02_001.png", {0.f,0.f,80.f,80.f});
	scrollBG->setContentSize(ccp(320.f, 230.f));
	scrollBG->setPosition(ccp(280.f,125.f));
	scrollBG->setOpacity(100.f);
	scrollBG->setID("hacks-bg");
	bg->addChild(scrollBG);

	//Scroll Layer
	auto scrollLayer = ScrollLayer::create({320.f,230.f});
	auto content = CCMenu::create();
	content->registerWithTouchDispatcher();
	content->setPosition(scrollLayer->getPosition());
	content->setContentSize(scrollLayer->getContentSize());
	content->setID("hacks-menu");
	scrollLayer->m_contentLayer->addChild(content);
	scrollLayer->setTouchEnabled(true);
	scrollBG->addChild(scrollLayer);

	//Ugh this code will be fixed later. It is super bad right now.
	for (size_t i = 0; i < Client::instance->sections.size(); i++) {
		auto section = Client::instance->sections[i];
		if (!section->id.compare("universal-section")) {
			for (size_t h = 0; h < section->hacks.size(); h++) {
				auto hack = section->hacks[h];
				hack->addHackToMenu(hack, content, ccp(65.f+160*(h%2), content->getContentHeight() - 25 - (40 * floor(h / 2))));
			}
		}
	}

	scrollLayer->moveToTop();
	scrollLayer->enableScrollWheel();

	handleTouchPriority(this);
	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);
	this->setMouseEnabled(true);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -500, true);

	this->setID("andesite-menu");

	return true;
}

void HackMenu::onClose(CCObject* p0) {
	this->removeFromParentAndCleanup(true);
}

HackMenu* HackMenu::create() {
	auto ret = new HackMenu();
	if (ret && ret->init(450.f,300.f)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
};