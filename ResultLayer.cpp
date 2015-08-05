#include "ResultLayer.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "GameSharing.h"
#include "TransitionSlideBounce.h"
#include "SoundManager.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;


ResultLayer::ResultLayer()
{
}


ResultLayer::~ResultLayer()
{
}


bool ResultLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//this->scheduleUpdate();

	auto dispatcher = this->getEventDispatcher();

	auto csb = CSLoader::createNode("resultLayer.csb");
	this->addChild(csb);

	_Img_BlackAlpha = (Sprite*)csb->getChildByName("img_black_alpha");
	_Img_BlackAlpha->setOpacity(0);

	_Img_Center = (Sprite*)csb->getChildByName("img_center");
	_Img_Center->setOpacity(0);

	_Img_Bankruptcy = (Sprite*)_Img_Center->getChildByName("img_bankruptcy");
	_Img_Bankruptcy->setOpacity(0);

	_Btn_GoHome = (Button*)_Img_Center->getChildByName("btn_gohome");
	_Btn_GoHome->addTouchEventListener(SoundManager::GetBtnTouchListener());

	_Btn_Retry = (Button*)_Img_Center->getChildByName("btn_retry");
	_Btn_Retry->addTouchEventListener(SoundManager::GetBtnTouchListener());

	_Val_Total = (Text*)_Img_Center->getChildByName("val_total");

	_Val_PlayTime = (Text*)_Img_Center->getChildByName("val_playtime");

	_Btn_GoHome->addClickEventListener([](Ref* ref)
	{
		Director::getInstance()->replaceScene(TitleScene::createScene());
	});

	_Btn_Retry->addClickEventListener([](Ref* ref)
	{
		//Director::getInstance()->replaceScene(TransitionSlideBounceL::create(1.0f, GameScene::createScene()));
		Director::getInstance()->replaceScene(GameScene::createScene());
	});

	_Val_Total->setString(String::createWithFormat("$%d", _Score)->getCString());

	_Val_PlayTime->setString(String::createWithFormat("%dsec", _PlayTime)->getCString());


	auto blackAlphaAction = FadeIn::create(0.5f);
	auto bankruptcyAction = FadeIn::create(1.5f);
	auto centerAction = EaseBounceOut::create(EaseInOut::create(MoveBy::create(1.0f, Vec2(720.0f, 0.0f)), 4.0f));

	this->runAction(Sequence::create(
						TargetedAction::create(_Img_BlackAlpha, blackAlphaAction),
						TargetedAction::create(_Img_Center, FadeIn::create(0.5f)),
						TargetedAction::create(_Img_Bankruptcy, bankruptcyAction),
						TargetedAction::create(_Img_Center, centerAction),
						nullptr));

	//GameSharing::SubmitScore(_Score, 0);

	return true;
}

