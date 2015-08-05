#pragma once
#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

class PauseLayer
	: public cocos2d::Layer
{
private:
	CC_DISALLOW_COPY_AND_ASSIGN(PauseLayer);

	std::function<void()> _ContinueCallback = nullptr, _StopCallback = nullptr;

	cocos2d::Sprite* _Img_Pause;
	cocos2d::Sprite* _Img_Count[3];
	cocos2d::Sprite* _Img_Go;

	cocos2d::ui::Button* _Btn_Continue, *_Btn_Stop;

	int _CurCount = 3;

public:
	PauseLayer();
	~PauseLayer();

	CREATE_FUNC(PauseLayer);

	virtual bool init() override;

	void SetContinueCallback(std::function<void()> func)
	{
		_ContinueCallback = func;
	}

	void SetStopCallback(std::function<void()> func)
	{
		_StopCallback = func;
	}
};

