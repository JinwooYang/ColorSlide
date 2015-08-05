#include "TitleScene.h"
#include "GameScene.h"
#include "GameSharing.h"
#include "AudioEngine.h"
#include "TransitionSlideBounce.h"
#include "SoundManager.h"


USING_NS_CC;
using namespace cocostudio;
using namespace ui;

const float transitionSpeed = 1.0f;

Point g_ScenePos[3];

//Point g_TitlePos;
//Point g_SettingPos;
//Point g_InfoPos;

TitleScene::TitleScene()
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
	auto winSize = Director::getInstance()->getWinSize();

	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		switch (_State)
		{
		case State::TITLE:
			Director::getInstance()->end();
			break;

		default:
			MoveScene(State::TITLE);
			break;
		}
	}
}



void TitleScene::MoveScene(State state)
{
	auto winSize = Director::getInstance()->getWinSize();

	auto move = MoveTo::create(transitionSpeed, g_ScenePos[state]);

	_State = state;

	_CSB->stopAllActions();
	_CSB->runAction(Sequence::create(EaseBounceOut::create(EaseInOut::create(move, 4.0f))//, CallFunc::create([&]()
		, nullptr));
}

bool TitleScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->scheduleUpdate();

	_State = State::TITLE;

	auto winSize = Director::getInstance()->getWinSize();

	g_ScenePos[State::TITLE] = Point(winSize.width / 2, winSize.height / 2);
	g_ScenePos[State::SETTING] = Point(g_ScenePos[State::TITLE].x + winSize.width, g_ScenePos[State::TITLE].y);
	g_ScenePos[State::INFO] = Point(g_ScenePos[State::TITLE].x - winSize.width, g_ScenePos[State::TITLE].y);

#pragma region Load CSB

	_CSB = CSLoader::createNode("titleScene.csb");
	_CSB->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_CSB->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(_CSB);

#pragma endregion

#pragma region Load titleScene Entity

	_Img_Cloud_Move = (Sprite*)_CSB->getChildByName("img_cloud_move");
	_Img_Sun = (Sprite*)_CSB->getChildByName("img_sun");
	_Img_Fire_Move = (Sprite*)_CSB->getChildByName("img_fire_move");
	_Img_MainCharacter = (Sprite*)_CSB->getChildByName("img_maincharacter");

	_Btn_Set = (Button*)_CSB->getChildByName("btn_set");
	_Btn_Set->addTouchEventListener(SoundManager::GetBtnTouchListener());
	_Btn_Set->addClickEventListener([=](Ref*)
	{
		MoveScene(State::SETTING);
	});

	_Btn_Info = (Button*)_CSB->getChildByName("btn_info");
	_Btn_Info->addTouchEventListener(SoundManager::GetBtnTouchListener());
	_Btn_Info->addClickEventListener([=](Ref*)
	{
		MoveScene(State::INFO);
	});

	_Btn_Play = (Button*)_CSB->getChildByName("btn_play");
	_Btn_Play->addTouchEventListener(SoundManager::GetBtnTouchListener());
	_Btn_Play->addClickEventListener([=](Ref*)
	{
		Director::getInstance()->replaceScene(TransitionSlideBounceB::create(1.5f, GameScene::createScene()));
	});

	_Btn_LeaderBoard = (Button*)_CSB->getChildByName("btn_leaderboard");
	_Btn_LeaderBoard->addClickEventListener([=](Ref*)
	{
		//GameSharing::ShowLeaderboards(0);
	});

	_Img_Cloud_Move->runAction(RepeatForever::create(Sequence::create(MoveTo::create(20.0f, Vec2(-2160, 0)),
																	  MoveTo::create(0.0f, Vec2::ZERO), nullptr)));
	_Img_Fire_Move->runAction(RepeatForever::create(RotateBy::create(7.0f, 360)));

#pragma endregion

#pragma region Load settingScene Entity

	_Chk_BGM = MyCheckBox::create();
	_Chk_SFX = MyCheckBox::create();

	_Chk_BGM->setPosition(440, 745);
	_Chk_SFX->setPosition(440, 596);

	_CSB->addChild(_Chk_BGM);
	_CSB->addChild(_Chk_SFX);

	_Chk_BGM->SetCheck(UserDefault::getInstance()->getBoolForKey("BGM", true));
	_Chk_BGM->SetCheckEventCallBack([=](bool check)
	{
		SoundManager::SetBGMOn(check);
		UserDefault::getInstance()->setBoolForKey("BGM", check);
	});

	_Chk_SFX->SetCheck(UserDefault::getInstance()->getBoolForKey("SFX", true));
	_Chk_SFX->SetCheckEventCallBack([](bool check)
	{
		SoundManager::SetSFXOn(check);
		UserDefault::getInstance()->setBoolForKey("SFX", check);
	});

	_Btn_Set_GoHome = (Button*)_CSB->getChildByName("btn_set_gohome");
	_Btn_Set_GoHome->addTouchEventListener(SoundManager::GetBtnTouchListener());
	_Btn_Set_GoHome->addClickEventListener([=](Ref*)
	{
		MoveScene(State::TITLE);
	});

#pragma endregion

#pragma region Load infoScene Entity

	_Btn_Info_GoHome = (Button*)_CSB->getChildByName("btn_info_gohome");
	_Btn_Info_GoHome->addTouchEventListener(SoundManager::GetBtnTouchListener());
	_Btn_Info_GoHome->addClickEventListener([=](Ref*)
	{
		MoveScene(State::TITLE);
	});

	_Btn_Kim = SpeechBubble::create(Developer::KIM);
	_Btn_Kim->setPosition(1709, 645);
	_CSB->addChild(_Btn_Kim);

	_Btn_Yang = SpeechBubble::create(Developer::YANG);
	_Btn_Yang->setPosition(1899, 645);
	_CSB->addChild(_Btn_Yang);

#pragma endregion

#pragma region Set Listener

	auto dispatcher = this->getEventDispatcher();
	_KeyListener = EventListenerKeyboard::create();
	_KeyListener->onKeyReleased = CC_CALLBACK_2(TitleScene::onKeyReleased, this);
	dispatcher->addEventListenerWithSceneGraphPriority(_KeyListener, this);


	_TouchListener = EventListenerTouchOneByOne::create();
	_TouchListener->onTouchBegan = [&](Touch* touch, Ref*)->bool
	{
		auto touchPos = touch->getLocation();
		auto winSize = Director::getInstance()->getWinSize();
		touchPos.x += winSize.width;

		if (_Img_Sun->getBoundingBox().containsPoint(touchPos))
		{
			//GameSharing::UnlockAchivement(1);
		}
		//else if (_Img_Cristal->getBoundingBox().containsPoint(touchPos))
		//{
		//	GameSharing::UnlockAchivement(2);
		//}

		return true;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_TouchListener, this);

#pragma endregion


	//auto simpleAudio = CocosDenshion::SimpleAudioEngine::getInstance();
	//if (!simpleAudio->isBackgroundMusicPlaying())
	//{
	//	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm.mp3", true);
	//}

	if (SoundManager::GetBGMID() == experimental::AudioEngine::INVALID_AUDIO_ID)
	{
		SoundManager::PlayBGM("bgm.mp3", true, 0.2f);
	}


	return true;
}


void TitleScene::update(float dt)
{
}


void TitleScene::onExit()
{
	Layer::onExit();
	auto dispatcher = this->getEventDispatcher();
	dispatcher->removeEventListener(_KeyListener);
	dispatcher->removeEventListener(_TouchListener);
}
