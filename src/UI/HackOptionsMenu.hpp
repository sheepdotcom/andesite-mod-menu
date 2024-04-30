#pragma once

#include "../Hacks/Hacks.hpp"

using namespace geode::prelude;

class HackOptionsMenu : public CCLayerColor {
public:
	Hack* currentHack = nullptr;

	void onClose(CCObject* p0);
	bool init(Hack* hack, float mWidth, float mHeight);
	static HackOptionsMenu* create(Hack* hack);
};