#pragma once

#include "../Hacks/Hacks.hpp"
#include "../Client.hpp"

using namespace geode::prelude;

class HackMenu : public CCLayerColor {
public:
	CCMenu* m_content;
	static inline Hacks* currentSection = nullptr;

	void onOptions(CCObject* p0);
	void regenSection(Hacks* section);
	bool init(float mWidth, float mHeight);
	void onClose(CCObject* p0);
	void keyBackClicked();
	static HackMenu* create();
};