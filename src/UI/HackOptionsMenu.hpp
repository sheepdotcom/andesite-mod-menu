#pragma once

#include "../Hacks/Hacks.hpp"

using namespace geode::prelude;

class HackOptionsMenu : public CCLayerColor {
public:
	void onClose(CCObject* p0);
	void keyBackClicked();
	bool init(Hack* hack, float mWidth, float mHeight);
	static HackOptionsMenu* create(Hack* hack);
};