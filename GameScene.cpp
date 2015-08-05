#include "GameScene.h"
#include "TitleScene.h"
#include "ResultLayer.h"
#include "GameSharing.h"
#include "PauseLayer.h"
#include "TransitionSlideBounce.h"
#include "SoundManager.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

const char* g_MomSpend[5] = {"ColorSlideResources/gameScene/mom/img_bohum.png",
							"ColorSlideResources/gameScene/mom/img_mopee.png" ,
							"ColorSlideResources/gameScene/mom/img_neck_ring.png" ,
							"ColorSlideResources/gameScene/mom/img_ring.png" ,
							"ColorSlideResources/gameScene/mom/img_tax.png" };

const char* g_SonSpend[5] = { "ColorSlideResources/gameScene/son/img_hyunzil.png",
								"ColorSlideResources/gameScene/son/img_money.png",
								"ColorSlideResources/gameScene/son/img_pc.png",
								"ColorSlideResources/gameScene/son/img_game.png",
								"ColorSlideResources/gameScene/son/img_study.png" };

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}


void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		this->OpenPauseLayer();
	}
}


bool GameScene::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
	{
		return false;
	}
	this->scheduleUpdate();

	_RemainTime = _MaxTime;
	_Score = _ShowScore = 0;
	_PauseLayerIsOpen = false;


	//Load UI
	_CSB = CSLoader::createNode("gameScene.csb");
	this->addChild(_CSB);

	_Img_Mom = (Sprite*)_CSB->getChildByName("img_mom");
	_Img_Son = (Sprite*)_CSB->getChildByName("img_son");

	_Timer = Node::create();
	this->addChild(_Timer);

	_Btn_Pause = (Button*)_CSB->getChildByName("game_btn_pause");
	_Btn_Pause->addTouchEventListener(SoundManager::GetBtnTouchListener());
	_Btn_Pause->addClickEventListener([&](Ref* ref)
	{
		this->OpenPauseLayer();
	});

	_Val_Score = (Text*)_CSB->getChildByName("game_val_score");
	_Val_Score->setString("$0");

	//_Val_Time = (Text*)_CSB->getChildByName("game_val_time");
	_Prg_Gauge = (LoadingBar*)_CSB->getChildByName("game_prg_gauge");


	//Add Listner
	auto dispatcher = this->getEventDispatcher();

	_KeyListener = EventListenerKeyboard::create();
	_KeyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	dispatcher->addEventListenerWithSceneGraphPriority(_KeyListener, this);


	//Create BlockBoard
	_CurBlockBoard = BlockBoard::create(3, 3, &_Score, &_RemainTime);
	this->addChild(_CurBlockBoard, 1);


	_MomTimerMax = cocos2d::random(0.3f, 3.0f);
	_SonTimerMax = cocos2d::random(0.3f, 3.0f);

	//Add Schedule
	_Timer->schedule([&](float dt)
	{
		_MomTimer += dt;
		_SonTimer += dt;

		if (_MomTimer > _MomTimerMax)
		{
			_MomTimer = 0.0f;
			_MomTimerMax = cocos2d::random(0.3f, 3.0f);
			auto money = Sprite::create(g_MomSpend[cocos2d::random(0, 4)]);
			money->setPosition(_Img_Mom->getPositionX(), _Img_Mom->getPositionY() + 50.0f);
			this->addChild(money);

			auto move = Sequence::create(MoveBy::create(0.3f, Vec2(100.0f, -5.0f)), MoveBy::create(4.0f, Vec2(0, 100)), nullptr);
			auto fadeOut = Sequence::create(FadeOut::create(4.3f), RemoveSelf::create(), nullptr);

			money->runAction(move);
			money->runAction(fadeOut);
		}

		if (_SonTimer > _SonTimerMax)
		{
			_SonTimer = 0.0f;
			_SonTimerMax = cocos2d::random(0.3f, 3.0f);
			auto money = Sprite::create(g_SonSpend[cocos2d::random(0, 4)]);
			money->setPosition(_Img_Son->getPositionX(), _Img_Son->getPositionY() + 50.0f);
			this->addChild(money);

			auto move = Sequence::create(MoveBy::create(0.3f, Vec2(100.0f, -5.0f)), MoveBy::create(4.0f, Vec2(0, 100)), nullptr);
			auto fadeOut = Sequence::create(FadeOut::create(4.3f), RemoveSelf::create(), nullptr);

			money->runAction(move);
			money->runAction(fadeOut);
		}


		_PlayTime += dt;
		_RemainTime -= dt;
		if (_RemainTime <= 0.0f)
		{
			ShowResult();
			_Timer->unschedule("timer");
		}
	}, 0.1f, "timer");


	//GameSharing::UnlockAchivement(0);

	auto waitLayer = CSLoader::createNode("waitLayer.csb");
	this->addChild(waitLayer, 5);

	_Count_3 = (Sprite*)waitLayer->getChildByName("img_count_3");

	_Count_2 = (Sprite*)waitLayer->getChildByName("img_count_2");

	_Count_1 = (Sprite*)waitLayer->getChildByName("img_count_1");

	_Count_Go = (Sprite*)waitLayer->getChildByName("img_count_go");

	auto fadeInOut = Sequence::create(FadeIn::create(0.5f), FadeOut::create(0.5f), nullptr);

	auto count_3 = TargetedAction::create(_Count_3, fadeInOut);
	auto count_2 = TargetedAction::create(_Count_2, fadeInOut->clone());
	auto count_1 = TargetedAction::create(_Count_1, fadeInOut->clone());
	auto go = TargetedAction::create(_Count_Go, fadeInOut->clone());


	this->runAction(Sequence::create(
		CallFunc::create([=](){ Pause(); }),
		count_3,
		count_2,
		count_1,
		go,
		CallFunc::create([=]()
		{
			Resume();
			this->scheduleUpdate();
			this->removeChild(waitLayer);
		}),
		nullptr));

	return true;
}


void GameScene::update(float dt)
{
	if (_CurBlockBoard->isRunning())
	{
		_CurBlockBoard->Update();
		if (_CurBlockBoard->IsClear())
		{
			if (++_Wave < 3)
			{
				_NextBlockBoard = BlockBoard::create(3, 3, &_Score, &_RemainTime);
			}
			else if (_Wave < 8)
			{
				_NextBlockBoard = BlockBoard::create(4, 4, &_Score, &_RemainTime);
			}
			else
			{
				_NextBlockBoard = BlockBoard::create(5, 5, &_Score, &_RemainTime);
			}

			this->addChild(_NextBlockBoard, 0);

			auto winSize = Director::getInstance()->getWinSize();
			auto move = MoveBy::create(0.2f, Vec2(winSize.width, 0));

			_CurBlockBoard->runAction(Sequence::create(EaseOut::create(move, 0.5f), RemoveSelf::create(), nullptr));
			_NextBlockBoard->runAction(Sequence::create(FadeIn::create(0.5f), CallFunc::create(std::bind([](BlockBoard* bb)
			{
				bb->setLocalZOrder(1);
			}, _NextBlockBoard)), nullptr));

			_CurBlockBoard = _NextBlockBoard;
			_NextBlockBoard = nullptr;
		}
	}

	UpdateScore();
	//_Val_Time->setString(String::createWithFormat("%0.0f", _RemainTime)->getCString());
	_Prg_Gauge->setPercent(_RemainTime / _MaxTime * 100.0f);
}


void GameScene::onExit()
{
	Layer::onExit();
	getEventDispatcher()->removeEventListener(_KeyListener);
}


void GameScene::Pause()
{
	_CurBlockBoard->PauseWithChild();
	_Timer->pause();
	_Btn_Pause->setEnabled(false);
	_Btn_Pause->setHighlighted(true);

}

void GameScene::Resume()
{
	_CurBlockBoard->ResumeWithChild();
	_Timer->resume();
	_Btn_Pause->setEnabled(true);
	_Btn_Pause->setHighlighted(false);
}

void GameScene::ShowResult()
{
	Pause();

	auto resultLayer = ResultLayer::create(_Score, _PlayTime);
	this->addChild(resultLayer, 10);
}


void GameScene::OpenPauseLayer()
{
	if (!_PauseLayerIsOpen)
	{
		_PauseLayerIsOpen = true;

		Pause();

		auto pauseLayer = PauseLayer::create();
		this->addChild(pauseLayer, 5);


		pauseLayer->SetContinueCallback([&, pauseLayer]()
		{
			Resume();
			_PauseLayerIsOpen = false;
			this->removeChild(pauseLayer);
		});


		pauseLayer->SetStopCallback([&, pauseLayer]()
		{
			ShowResult();
			this->removeChild(pauseLayer);
		});
	}
}


void GameScene::UpdateScore()
{
	static bool needToUpdate = false;

	static float gap = 0.0f;
	static int _OldScore = _Score;

	if (!needToUpdate || _OldScore != _Score)
	{
		needToUpdate = true;
		gap = (_Score - _ShowScore) / 30;
	}
	else if (needToUpdate)
	{
		_ShowScore += gap;

		if (_ShowScore >= _Score)
		{
			needToUpdate = false;
			_ShowScore = _Score;
		}

		_Val_Score->setString(String::createWithFormat("$%d", _ShowScore)->getCString());
	}

	_OldScore = _Score;
}