#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class AndesiteMenu : public FLAlertLayer {
protected:
	ScrollLayer* m_scrollLayer;
	CCMenu* m_content;
public:
	void useless(CCObject* p0);
	void addHackToMenu(CCPoint pos);
	bool init();
	void onClose(CCObject* p0);
	static AndesiteMenu* create();
};