#pragma once
#include "cocos2d.h"
#include "MyMacro.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "MyCheckBox.h"
#include "SpeechBubble.h"

class TitleScene
	: public cocos2d::Layer
{
	enum State{SETTING, TITLE, INFO};

private:
	CC_DISALLOW_COPY_AND_ASSIGN(TitleScene);
	TitleScene();
	~TitleScene();

private:
	State _State;
	
	cocos2d::EventListenerKeyboard* _KeyListener;
	cocos2d::EventListenerTouchOneByOne* _TouchListener;


	cocos2d::Node* _CSB;

	//title
	cocos2d::Sprite* _Img_Cloud_Move, *_Img_Sun, *_Img_Fire_Move, *_Img_MainCharacter;
	cocos2d::ui::Button* _Btn_Set, *_Btn_Info, *_Btn_Play, *_Btn_LeaderBoard;

	//setting
	MyCheckBox* _Chk_BGM, *_Chk_SFX;
	cocos2d::ui::Button* _Btn_How, *_Btn_Set_GoHome;


	//info
	cocos2d::ui::Button* _Btn_Info_GoHome;
	SpeechBubble* _Btn_Kim, *_Btn_Yang;


	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) override;

	void MoveScene(State state);

public:
	CREATE_FUNC(TitleScene);
	CREATE_SCENE_FUNC(TitleScene);

	virtual bool init() override;
	virtual void update(float dt) override;
	virtual void onExit() override;
};