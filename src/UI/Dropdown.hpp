#pragma once

using namespace geode::prelude;

class Dropdown : public CCMenu {
public:
	CCLabelBMFont* text;
	CCSize size;
	CCScale9Sprite* bg;
	CCSprite* btnSprite;
	CCMenuItemSpriteExtra* btn;
	std::vector<std::string> content;
	std::vector<CCMenuItemSpriteExtra*> btns;
	SEL_MenuHandler event;

	int selected = 0;
	bool open;

	void onToggleVisible(CCObject* p0);
	void setToggled(bool visible);
	void onPress(CCObject* p0);
	bool init(CCSize size, std::vector<std::string> content, SEL_MenuHandler callback, int selected);

	static Dropdown* create(CCSize size, std::vector<std::string> content, SEL_MenuHandler callback, int selected);
};