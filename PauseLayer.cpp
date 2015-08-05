#include "PauseLayer.h"
#include "SoundManager.h"

USING_NS_CC;
using namespace ui;

PauseLayer::PauseLayer()
{
}


PauseLayer::~PauseLayer()
{
}


bool PauseLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->scheduleUpdate();

	auto csb = CSLoader::createNode("pauseLayer.csb");
	this->addChild(csb);

	_Img_Pause = (Sprite*)csb->getChildByName("img_pause");

	for (int i = 0; i < 3; ++i)
	{
		_Img_Count[i] = (Sprite*)csb->getChildByName(String::createWithFormat("img_count_%d", i + 1)->getCString());
	}
	_Img_Go = (Sprite*)csb->getChildByName("img_count_go");


	_Btn_Continue = (Button*)csb->getChildByName("btn_continue");
	_Btn_Continue->addTouchEventListener(SoundManager::GetBtnTouchListener());
	_Btn_Continue->addClickEventListener([&](Ref*)
	{
		_Btn_Continue->setVisible(false);
		_Btn_Stop->setVisible(false);
		_Img_Pause->setVisible(false);

		auto fadeInOut = Sequence::create(FadeIn::create(0.5f), FadeOut::create(0.5f), nullptr);

		auto count_3 = TargetedAction::create(_Img_Count[2], fadeInOut);
		auto count_2 = TargetedAction::create(_Img_Count[1], fadeInOut->clone());
		auto count_1 = TargetedAction::create(_Img_Count[0], fadeInOut->clone());
		auto go = TargetedAction::create(_Img_Go, fadeInOut->clone());


		_Img_Go->runAction(Sequence::create(count_3,
											count_2,
											count_1,
											go,
											CallFunc::create([&]()
											{
												if (_ContinueCallback) _ContinueCallback();
											}),
											nullptr));
	});

	_Btn_Stop = (Button*)csb->getChildByName("btn_stop");
	_Btn_Stop->addTouchEventListener(SoundManager::GetBtnTouchListener());
	_Btn_Stop->addClickEventListener([&](Ref*)
	{
		if (_StopCallback) _StopCallback();
	});

	return true;
}