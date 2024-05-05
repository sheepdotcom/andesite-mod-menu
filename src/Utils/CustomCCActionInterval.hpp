#pragma once

using namespace geode::prelude;

//QOLMod code again, all this similar code will get this mod denied if I ever submit it to the index.
class CCContentSizeTo : public CCActionInterval {
public:
	static CCContentSizeTo* create(float duration, const CCSize& size) {
		CCContentSizeTo* ret = new CCContentSizeTo();
		if (ret && ret->initWithDuration(duration, size)) {
			ret->autorelease();
			return ret;
		}
		CC_SAFE_DELETE(ret);
		return nullptr;
	}

	virtual void update(float time) {
		if (this->target) {
			CCSize newSize(this->startSize.width + (this->endSize.width - this->startSize.width) * time,
				this->startSize.height + (this->endSize.height - this->startSize.height) * time);
			this->target->setContentSize(newSize);
		}
	}

protected:
	bool initWithDuration(float duration, const CCSize& size) {
		if (CCActionInterval::initWithDuration(duration)) {
			this->endSize = size;
			return true;
		}
		return false;
	}

	void startWithTarget(CCNode* target) {
		CCActionInterval::startWithTarget(target);
		this->target = target;
		this->startSize = target->getContentSize();
	}

	CCSize endSize;
	CCSize startSize;
	CCNode* target;
};

class CCScaleToWithDelay : public CCActionInterval {
public:
	static CCScaleToWithDelay* create(float duration, float scale, float delay) {
		CCScaleToWithDelay* ret = new CCScaleToWithDelay();
		if (ret && ret->initWithDuration(duration, scale, scale, delay)) {
			ret->autorelease();
			return ret;
		}
		CC_SAFE_DELETE(ret);
		return nullptr;
	}

	static CCScaleToWithDelay* create(float duration, float sx, float sy, float delay) {
		CCScaleToWithDelay* ret = new CCScaleToWithDelay();
		if (ret && ret->initWithDuration(duration, sx, sy, delay)) {
			ret->autorelease();
			return ret;
		}
		CC_SAFE_DELETE(ret);
		return nullptr;
	}

	virtual void update(float time) {
		if (this->target) {
			//The math at the end basically subtracts the delay (as a percentage of 1) from the time (0-1 in value) and caps it at 0, then it multiplies by this which makes sure that when time reaches 1, this will be 1 as well, so we dont have any wierd scaling going on.
			float newScaleX = this->startScaleX + (this->endScaleX - this->startScaleX) * (std::max(time - this->delay, 0.f) * (1 / (1 - this->delay))); //Math equation found through desmos after some testing.
			float newScaleY = this->startScaleY + (this->endScaleY - this->startScaleY) * (std::max(time - this->delay, 0.f) * (1 / (1 - this->delay))); //Copied here for scale y as well.
			this->target->setScale(newScaleX, newScaleY);
		}
	}
	
protected:
	bool initWithDuration(float duration, float sx, float sy, float delay) {
		if (CCActionInterval::initWithDuration(duration + delay)) {
			this->endScaleX = sx;
			this->endScaleY = sy;
			this->delay = delay / (duration + delay);
			return true;
		}
		return false;
	}

	void startWithTarget(CCNode* target) {
		CCActionInterval::startWithTarget(target);
		this->target = target;
		this->startScaleX = target->getScaleX();
		this->startScaleY = target->getScaleY();
	}

	float endScaleX;
	float endScaleY;
	float startScaleX;
	float startScaleY;
	float delay;
	CCNode* target;
};