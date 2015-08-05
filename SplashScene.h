#pragma once
#include "cocos2d.h"
#include "MyMacro.h"

class SplashScene
	: public cocos2d::LayerColor
{
private:
	CC_DISALLOW_COPY_AND_ASSIGN(SplashScene);
	CREATE_FUNC(SplashScene);

	SplashScene();
	~SplashScene();

	void KWCAction();
	void LogoAction();
	void BoxAction();
	void Box2Action();

private:
	cocos2d::Node* _CSB;
	cocos2d::Sprite* _Img_Box1, *_Img_Box2, *_Img_Logo, *_Img_KWC;

public:
	CREATE_SCENE_FUNC(SplashScene);

	virtual bool init() override;
	virtual void update(float dt) override;
	virtual void onExit() override;
};

