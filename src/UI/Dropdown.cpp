#include "Dropdown.hpp"
#include "../Utils/CustomCCActionInterval.hpp"

using namespace geode::prelude;

void Dropdown::onToggleVisible(CCObject* p0) {
	open = !open;
	setToggled(open);
}

void Dropdown::setToggled(bool visible) {
	auto animTime = 0.35f;
	bg->stopAllActions();
	bg->runAction(CCEaseOut::create(CCContentSizeTo::create(animTime, ccp(size.width, size.height + (open ? (content.size() * 20.f) : 0.f))), 2.0f)); //Math equations when coding be like
	
	btnSprite->runAction(CCEaseBackOut::create(CCRotateTo::create(animTime, open ? 180.f : 0.f)));
	
	if (!visible) std::reverse(btns.begin(), btns.end());
	for (size_t i = 0; i < btns.size(); i++) {
		btns[i]->stopAllActions();
		btns[i]->setEnabled(visible);
		btns[i]->runAction(CCEaseInOut::create(CCScaleToWithDelay::create(0.2f, open ? 1.f : 0.f, ((animTime / btns.size()) * i)), 2.0f));
	}
	if (!visible) std::reverse(btns.begin(), btns.end());
}

void Dropdown::onPress(CCObject* p0) {
	open = false;
	selected = static_cast<CCNode*>(p0)->getTag();

	text->setString(content[selected].c_str());

	for (size_t i = 0; i < btns.size(); i++) {
		static_cast<CCLabelBMFont*>(btns[i]->getChildByID("dropdown-option-label"))->setColor(selected == i ? ccColor3B{0, 255, 0} : ccColor3B{255, 255, 255});
	}

	setToggled(open);

	if (event) (this->*event)(p0);
}

//Custom Dropdown, sorry QOLMod again again
bool Dropdown::init(CCSize size, std::vector<std::string> content, SEL_MenuHandler callback, int selector) {
	if (!CCMenu::init()) return false;

	this->size = size;
	this->content = content;
	this->event = callback;

	this->setContentSize(size);
	bg = CCScale9Sprite::create("square02_small.png");
	bg->setContentSize(size);
	bg->setAnchorPoint(ccp(0.5f, 1.f));
	bg->setPosition(ccp(size.width / 2, size.height));
	bg->setOpacity(100);
	bg->setID("dropdown-bg");
	this->addChild(bg);

	btnSprite = CCSprite::createWithSpriteFrameName("edit_downBtn_001.png");
	btnSprite->setID("dropdown-arrow-sprite");
	btn = CCMenuItemSpriteExtra::create(btnSprite, this, menu_selector(Dropdown::onToggleVisible));
	btn->setPosition(ccp(size.width / 2, size.height / 2));
	btn->m_baseScale = 0.75f;
	btn->setScale(btn->m_baseScale);
	btn->m_animationEnabled = false;
	btn->setID("dropdown-arrow");
	btn->setContentSize(ccp(size.width / btn->getScaleX(), size.height / btn->getScaleY()));
	btnSprite->setPosition(ccp(btn->getContentWidth() - btnSprite->getContentWidth(), btn->getContentHeight() / 2));
	this->addChild(btn);

	text = CCLabelBMFont::create(content[selector].c_str(), "bigFont.fnt");
	text->setPosition(ccp((size.width / 2) - (btnSprite->getContentWidth() / 2), size.height / 2));
	text->limitLabelWidth(size.width - btnSprite->getContentWidth() - 10.f, 0.7f, 0.05f);
	text->setID("currently-selected-text");
	this->addChild(text);

	for (size_t c = 0; c < content.size(); c++) {
		auto label = CCLabelBMFont::create(content[c].c_str(), "bigFont.fnt");
		label->limitLabelWidth(size.width - 10.f, 0.7f, 0.01f);
		if (selector == c) label->setColor({0, 255, 0});
		label->setID("dropdown-option-label");

		auto btn = CCMenuItemSpriteExtra::create(label, this, menu_selector(Dropdown::onPress));
		btn->setPosition(ccp(size.width / 2, (size.height / 2) - ((c + 1) * 20.f)));
		btn->setScale(0.f);
		btn->setTag(c);
		btn->setID(content[c]);
		btn->setEnabled(false);
		this->addChild(btn);

		btns.push_back(btn);
	}

	handleTouchPriority(this);
	this->registerWithTouchDispatcher();

	return true;
}

Dropdown* Dropdown::create(CCSize size, std::vector<std::string> content, SEL_MenuHandler callback, int selector) {
	Dropdown* ret = new Dropdown();
	if (ret && ret->init(size, content, callback, selector)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}