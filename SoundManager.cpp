#include "SoundManager.h"
#include "AudioEngine.h"

USING_NS_CC;
using namespace experimental;
using namespace cocos2d::ui;

bool SoundManager::_BgmOn = true;
bool SoundManager::_SfxOn = true;
int SoundManager::_BgmID = AudioEngine::INVALID_AUDIO_ID;

SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

void SoundManager::SetBGMOn(bool on)
{
	_BgmOn = on;

	if (_BgmID != cocos2d::experimental::AudioEngine::INVALID_AUDIO_ID)
	{
		if (!on)
		{
			cocos2d::experimental::AudioEngine::pause(_BgmID);
		}
		else
		{
			cocos2d::experimental::AudioEngine::resume(_BgmID);
		}
	}
}


void SoundManager::PlayBGM(const char* file, bool loop, float volume)
{
	if (_BgmOn)
	{
		_BgmID = AudioEngine::play2d(file, true, volume);
	}
}


void SoundManager::PlaySFX(const char* file, float volume)
{
	if (_SfxOn)
	{
		AudioEngine::play2d(file, false, volume);
	}
}

int SoundManager::GetBGMID()
{
	return _BgmID;
}

std::function<void(cocos2d::Ref*, Widget::TouchEventType)> SoundManager::GetBtnTouchListener()
{
	auto func = [](Ref* ref, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			SoundManager::PlaySFX("sfx/btn_push.mp3");
			//log("BEGAN");
			break;
		case Widget::TouchEventType::ENDED:
			SoundManager::PlaySFX("sfx/btn_pop.mp3");
			break;

		default:
			break;
		}
	};

	return func;
}
