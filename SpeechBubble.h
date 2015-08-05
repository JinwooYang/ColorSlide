#pragma once
#include "cocos2d.h"

enum Developer{KIM, YANG};

class SpeechBubble
	: public cocos2d::Sprite
{
private:
	CC_DISALLOW_COPY_AND_ASSIGN(SpeechBubble);

	Developer _Dev;

	cocos2d::EventListenerTouchOneByOne* _TouchListener;

	bool _IsSelected = false;

public:
	SpeechBubble();
	~SpeechBubble();

	static SpeechBubble* create(Developer dev)
	{
		auto bubble = new SpeechBubble;

		if (bubble && bubble->init(dev))
		{
			bubble->autorelease();
		}
		else
		{
			delete bubble;
			bubble = nullptr;
		}

		return bubble;
	};

	bool init(Developer dev);

};

