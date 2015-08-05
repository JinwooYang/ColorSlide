#pragma once
#include "cocos2d.h"

class TransitionSlideBounceL
	: public cocos2d::TransitionSlideInL
{
public:
	TransitionSlideBounceL() {};
	~TransitionSlideBounceL() {};

	static TransitionSlideBounceL* create(float t, cocos2d::Scene* scene)
	{
		TransitionSlideBounceL* newScene = new (std::nothrow) TransitionSlideBounceL();
		if (newScene && newScene->initWithDuration(t, scene))
		{
			newScene->autorelease();
			return newScene;
		}
		CC_SAFE_DELETE(newScene);
		return nullptr;
	}

	virtual cocos2d::ActionInterval* easeActionWithAction(cocos2d::ActionInterval* action) override
	{
		return cocos2d::EaseBounceOut::create(cocos2d::EaseInOut::create(action, 4.0f));
	}
};


class TransitionSlideBounceR
	: public cocos2d::TransitionSlideInR
{
public:
	TransitionSlideBounceR() {};
	~TransitionSlideBounceR() {};

	static TransitionSlideBounceR* create(float t, cocos2d::Scene* scene)
	{
		TransitionSlideBounceR* newScene = new (std::nothrow) TransitionSlideBounceR();
		if (newScene && newScene->initWithDuration(t, scene))
		{
			newScene->autorelease();
			return newScene;
		}
		CC_SAFE_DELETE(newScene);
		return nullptr;
	}

	virtual cocos2d::ActionInterval* easeActionWithAction(cocos2d::ActionInterval* action) override
	{
		return cocos2d::EaseBounceOut::create(cocos2d::EaseInOut::create(action, 4.0f));
	}
};


class TransitionSlideBounceB
	: public cocos2d::TransitionSlideInB
{
public:
	TransitionSlideBounceB() {};
	~TransitionSlideBounceB() {};

	static TransitionSlideBounceB* create(float t, cocos2d::Scene* scene)
	{
		TransitionSlideBounceB* newScene = new (std::nothrow) TransitionSlideBounceB();
		if (newScene && newScene->initWithDuration(t, scene))
		{
			newScene->autorelease();
			return newScene;
		}
		CC_SAFE_DELETE(newScene);
		return nullptr;
	}

	virtual cocos2d::ActionInterval* easeActionWithAction(cocos2d::ActionInterval* action) override
	{
		return cocos2d::EaseBounceOut::create(cocos2d::EaseInOut::create(action, 4.0f));
	}
};

