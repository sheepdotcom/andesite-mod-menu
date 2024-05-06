#include "HackMenu.hpp"

using namespace geode::prelude;

void HackMenu::onOptions(CCObject* p0) {
	MoreOptionsLayer::create()->show();
}

void HackMenu::regenSection(Hacks* section) {
	m_content->removeAllChildrenWithCleanup(true);
	for (size_t i = 0; i < section->hacks.size(); i++) {
		section->hacks[i]->addHackToMenu(section->hacks[i], m_content, ccp(65.f + 160 * (i % 2), m_content->getContentHeight() - 25 - (40 * floor(i / 2))));
	}
}

bool HackMenu::init(float mWidth, float mHeight) {
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	if (!CCLayerColor::initWithColor({0,0,0,105})) return false;

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

	//Sections Layer Background
	auto sectionsBG = CCScale9Sprite::create("square02_001.png", {0.f,0.f,80.f,80.f});
	sectionsBG->setContentSize(ccp(100.f, 230.f));
	sectionsBG->setPosition(ccp(60.f, 125.f));
	sectionsBG->setOpacity(100.f);
	sectionsBG->setID("sections-bg");
	bg->addChild(sectionsBG);

	//Sections Layer
	auto sectionsLayer = ScrollLayer::create({100.f, 230.f});
	auto sectionsContent = CCMenu::create();
	sectionsContent->registerWithTouchDispatcher();
	sectionsContent->setPosition(sectionsLayer->getPosition());
	sectionsContent->setContentSize(sectionsLayer->getContentSize());
	sectionsContent->setID("sections-menu");
	sectionsLayer->m_contentLayer->addChild(sectionsContent);
	sectionsLayer->setTouchEnabled(true);
	sectionsBG->addChild(sectionsLayer);

	currentSection = Client::GetSection("universal");

	//Add Sections To Sections Layer
	for (size_t s = 0; s < Client::instance->sections.size(); s++) {
		Client::instance->sections[s]->addSectionToMenu(
			Client::instance->sections[s],
			sectionsContent,
			ccp(50.f, 210.f - (s * 35))
		);
	}

	sectionsLayer->moveToTop();
	sectionsLayer->enableScrollWheel();

	//Scroll Layer Background
	auto scrollBG = CCScale9Sprite::create("square02_001.png", {0.f,0.f,80.f,80.f});
	scrollBG->setContentSize(ccp(320.f, 230.f));
	scrollBG->setPosition(ccp(280.f, 125.f));
	scrollBG->setOpacity(100.f);
	scrollBG->setID("hacks-bg");
	bg->addChild(scrollBG);

	//Scroll Layer
	auto scrollLayer = ScrollLayer::create({320.f, 230.f});
	m_content = CCMenu::create();
	m_content->registerWithTouchDispatcher();
	m_content->setPosition(scrollLayer->getPosition());
	m_content->setContentSize(scrollLayer->getContentSize());
	m_content->setID("hacks-menu");
	scrollLayer->m_contentLayer->addChild(m_content);
	scrollLayer->setTouchEnabled(true);
	scrollBG->addChild(scrollLayer);

	//Add Hack Buttons To The Menu
	HackMenu::regenSection(currentSection);

	//Stuff Below Here Does Things
	scrollLayer->moveToTop();
	scrollLayer->enableScrollWheel();
	this->setZOrder(257); //Make sure it goes above things like the prism menu button

	handleTouchPriority(this, true);
	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);
	this->setMouseEnabled(true);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -482, true);

	this->setID("andesite-menu");

	return true;
}

void HackMenu::onClose(CCObject* p0) {
	this->removeFromParentAndCleanup(true);
}

void HackMenu::keyBackClicked() {
	HackMenu::onClose(nullptr);
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