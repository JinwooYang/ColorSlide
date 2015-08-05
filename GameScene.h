#pragma once
#include "cocos2d.h"
#include "MyMacro.h"
#include "BlockBoard.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "PauseLayer.h"

class GameScene final
	: public cocos2d::LayerColor
{
private:
	CC_DISALLOW_COPY_AND_ASSIGN(GameScene);
	CREATE_FUNC(GameScene);

	GameScene();
	~GameScene();

private:
	BlockBoard* _CurBlockBoard, *_NextBlockBoard;

	int _Wave = 0;

	float _MomTimerMax, _SonTimerMax;
	float _MomTimer = 0.0f, _SonTimer = 0.0f;
	float _PlayTime = 0.0f;
	const float _MaxTime = 30.0f;
	float _RemainTime = _MaxTime;
	int _Score = 0, _ShowScore = 0;
	bool _PauseLayerIsOpen = false;

	cocos2d::Node* _CSB, *_Timer;
	cocos2d::Sprite* _Img_Mom, *_Img_Son;
	cocos2d::Sprite* _Count_3, *_Count_2, *_Count_1, *_Count_Go;
	cocos2d::ui::Button* _Btn_Pause;
	cocos2d::ui::Text* _Val_Score;
	cocos2d::ui::LoadingBar* _Prg_Gauge;
	//cocos2d::ui::Text* *_Val_Time;

	cocos2d::EventListenerKeyboard* _KeyListener;

	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;

	void Pause();
	void Resume();
	void ShowResult();
	void OpenPauseLayer();
	void UpdateScore();
public:
	CREATE_SCENE_FUNC(GameScene);

	virtual bool init() override;
	virtual void update(float dt) override;
	virtual void onExit() override;

};

