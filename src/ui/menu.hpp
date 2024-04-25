#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class AndesiteMenu : public FLAlertLayer {
public:
	void useless(CCObject* p0);
	void addHackToMenu(CCNode* menu);
	bool init();
	void onClose(CCObject* p0);
	static AndesiteMenu* create();
};