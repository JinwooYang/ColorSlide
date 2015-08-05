#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <functional>

class SoundManager
{
private:
	SoundManager();
	~SoundManager();

	static bool _BgmOn,_SfxOn;
	static int _BgmID;

public:
	static void SetBGMOn(bool on);
	static void SetSFXOn(bool on)
	{
		_SfxOn = on;
	}

	static void PlayBGM(const char* file, bool loop = true, float volume = 1.0f);
	static void PlaySFX(const char* file, float volume = 1.0f);

	static int GetBGMID();

	static std::function<void(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType)> GetBtnTouchListener();
};

