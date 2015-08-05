#include "SpeechBubble.h"
#include "SoundManager.h"

USING_NS_CC;

enum {UP, DOWN};

char* BTN_IMG[2][2] = { "ColorSlideResources/titleScene/chk_kbs_design_up.png",
						"ColorSlideResources/titleScene/chk_kbs_design_down.png",
						"ColorSlideResources/titleScene/chk_yjw_program_up.png",
						"ColorSlideResources/titleScene/chk_yjw_program_down.png"};


SpeechBubble::SpeechBubble()
{
}


SpeechBubble::~SpeechBubble()
{
	this->getEventDispatcher()->removeEventListener(_TouchListener);
}


bool SpeechBubble::init(Developer dev)
{
	_Dev = dev;
	this->initWithFile(BTN_IMG[dev][UP]);

	auto dispatcher = this->getEventDispatcher();

	_TouchListener = EventListenerTouchOneByOne::create();
	_TouchListener->onTouchBegan = [&](Touch* touch, Event*)->bool
	{
		auto box = this->getBoundingBox();
		auto worldPos = this->getWorldPosition();
		box.origin.x = (worldPos.x - box.size.width / 2);

		if (box.containsPoint(touch->getLocation()))
		{
			_IsSelected = !_IsSelected;

			(_IsSelected) ? this->initWithFile(BTN_IMG[_Dev][DOWN]) :
							this->initWithFile(BTN_IMG[_Dev][UP]);
			(_IsSelected) ? SoundManager::PlaySFX("sfx/btn_push.mp3") :
							SoundManager::PlaySFX("sfx/btn_pop.mp3");
			
		}

		return true;
	};
	_TouchListener->onTouchCancelled = [&](Touch* touch, Event*)
	{
		_IsSelected = false;
	};

	dispatcher->addEventListenerWithSceneGraphPriority(_TouchListener, this);

	this->scheduleUpdate();

	return true;
}