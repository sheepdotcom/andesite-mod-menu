#pragma once

#include "../Hacks/Hacks.hpp"
#include "../Client.hpp"

using namespace geode::prelude;

class HackMenu : public CCLayerColor {
public:
	void onOptions(CCObject* p0);
	bool init(float mWidth, float mHeight);
	void onClose(CCObject* p0);
	static HackMenu* create();
};