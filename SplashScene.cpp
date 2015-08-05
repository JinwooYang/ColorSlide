#include "SplashScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "StoryScene.h"

USING_NS_CC;

SplashScene::SplashScene()
{
}


SplashScene::~SplashScene()
{
}

void SplashScene::KWCAction()
{
	auto delay = DelayTime::create(1.0f);
	auto fadeIn = FadeIn::create(0.5f);
	auto kwcAction = Sequence::create(delay, fadeIn, delay->clone(), fadeIn->reverse(), delay->clone(), CallFunc::create([&](){ LogoAction(); }), nullptr);

	_Img_KWC->runAction(kwcAction);
}

void SplashScene::LogoAction()
{
	auto fadeIn = FadeIn::create(0.5f);
	auto logoAction = Sequence::create(fadeIn, DelayTime::create(0.2f), nullptr);

	_Img_Logo->runAction(logoAction);

	BoxAction();
}

void SplashScene::BoxAction()
{
	float angle = 10.0f;

	auto fadeIn = FadeIn::create(0.5f);
	auto tilt = Sequence::create(RotateTo::create(0.1f, angle), RotateTo::create(0.1f, -angle), RotateTo::create(0.1f, angle), RotateTo::create(0.1f, 0.0f), nullptr);
	
	_Img_Box2->runAction(Sequence::create(fadeIn, tilt, nullptr));
	_Img_Box1->runAction(Sequence::create(
		fadeIn->clone(),
		DelayTime::create(0.2f),
		tilt->clone(),
		DelayTime::create(1.0f),
		CallFunc::create([]()
		{
			//if (UserDefault::getInstance()->getBoolForKey("FIRST_RUN", true))
			//{
			//	UserDefault::getInstance()->setBoolForKey("FIRST_RUN", false);
			//	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, StoryScene::createScene()));
			//}
			//else
			{
				Director::getInstance()->replaceScene(TransitionFade::create(0.5f, TitleScene::createScene()));
			}
		}),
		nullptr));
}

bool SplashScene::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
	{
		return false;
	}
	this->scheduleUpdate();

	_CSB = CSLoader::createNode("splashScene.csb");
	this->addChild(_CSB);

	_Img_Box1 = (Sprite*)_CSB->getChildByName("img_box1");
	_Img_Box1->setOpacity(0);

	_Img_Box2 = (Sprite*)_CSB->getChildByName("img_box2");
	_Img_Box2->setOpacity(0);

	_Img_Logo = (Sprite*)_CSB->getChildByName("img_logo");
	_Img_Logo->setOpacity(0);

	_Img_KWC = (Sprite*)_CSB->getChildByName("img_kwc");
	_Img_KWC->setOpacity(0);

	KWCAction();
	return true;
}


void SplashScene::update(float dt)
{
	//Director::getInstance()->replaceScene(TitleScene::createScene());
}


void SplashScene::onExit()
{
	Layer::onExit();
}