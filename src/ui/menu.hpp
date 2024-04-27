#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class AndesiteMenu : public FLAlertLayer {
public:
	ScrollLayer* m_scrollLayer;
	CCMenu* m_content;
	void useless(CCObject* p0);
	void onOptions(CCObject* p0);
	void addHackToMenu(CCPoint pos);
	bool init(float mWidth, float mHeight);
	void onClose(CCObject* p0);
	static AndesiteMenu* create();
};