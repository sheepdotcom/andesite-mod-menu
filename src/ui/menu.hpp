#pragma once

#include "../hacks/hacks.hpp"
#include "../client.hpp"

using namespace geode::prelude;

class AndesiteMenu : public FLAlertLayer {
public:
	ScrollLayer* m_scrollLayer;
	CCMenu* m_content;

	void onOptions(CCObject* p0);
	bool init(float mWidth, float mHeight);
	void onClose(CCObject* p0);
	static AndesiteMenu* create();
};