#include "MyCheckBox.h"
#include "SoundManager.h"

USING_NS_CC;

enum {ON_UP, ON_DOWN, OFF_UP, OFF_DOWN};

char* BTN_IMAGE[4] = {"ColorSlideResources/titleScene/btn_on_up.png",
						"ColorSlideResources/titleScene/btn_on_down.png", 
						"ColorSlideResources/titleScene/btn_off_up.png", 
						"ColorSlideResources/titleScene/btn_off_down.png"};

MyCheckBox::MyCheckBox()
{
}


MyCheckBox::~MyCheckBox()
{
	this->getEventDispatcher()->removeEventListener(_TouchListener);
}


void MyCheckBox::SetCheck(bool check)
{
	_IsChecked = check;

	if (_IsChecked)
	{
		this->initWithFile(BTN_IMAGE[ON_UP]);
	}
	else
	{
		this->initWithFile(BTN_IMAGE[OFF_UP]);
	}
}

bool MyCheckBox::init()
{
	this->initWithFile(BTN_IMAGE[ON_UP]);

	auto dispatcher = this->getEventDispatcher();

	_TouchListener = EventListenerTouchOneByOne::create();
	_TouchListener->onTouchBegan = [&](Touch* touch, Event*)->bool
	{
		if (!_IsSelected)
		{
			auto box = this->getBoundingBox();
			auto worldPos = this->getWorldPosition();
			box.origin.x = (worldPos.x - box.size.width / 2);

			if (box.containsPoint(touch->getLocation()))
			{
				_IsSelected = true;
				_IsDown = true;

				(_IsChecked) ? this->initWithFile(BTN_IMAGE[ON_DOWN]) :
							   this->initWithFile(BTN_IMAGE[OFF_DOWN]);
				SoundManager::PlaySFX("sfx/btn_push.mp3");
			}
		}
		return true;
	};
	_TouchListener->onTouchMoved = [&](Touch* touch, Event*)
	{
		if (_IsSelected)
		{
			auto box = this->getBoundingBox();
			auto worldPos = this->getWorldPosition();
			box.origin.x = (worldPos.x - box.size.width / 2);

			auto touchPos = touch->getLocation();

			if (_IsDown && !box.containsPoint(touchPos))
			{
				_IsDown = false;
				(_IsChecked) ? this->initWithFile(BTN_IMAGE[ON_UP]) :
					this->initWithFile(BTN_IMAGE[OFF_UP]);
			}
			else if (!_IsDown && box.containsPoint(touchPos))
			{
				_IsDown = true;
				(_IsChecked) ? this->initWithFile(BTN_IMAGE[ON_DOWN]) :
					this->initWithFile(BTN_IMAGE[OFF_DOWN]);
			}
		}
	};
	_TouchListener->onTouchEnded = [&](Touch* touch, Event*)
	{
		if (_IsSelected)
		{
			auto box = this->getBoundingBox();
			auto worldPos = this->getWorldPosition();
			box.origin.x = (worldPos.x - box.size.width / 2);
			auto touchPos = touch->getLocation();

			if (_IsDown && box.containsPoint(touchPos))
			{
				_IsChecked = !_IsChecked;

				(_IsChecked) ? this->initWithFile(BTN_IMAGE[ON_UP]) :
					this->initWithFile(BTN_IMAGE[OFF_UP]);

				SoundManager::PlaySFX("sfx/btn_pop.mp3");

				if (_CheckEventCallBack) _CheckEventCallBack(_IsChecked);
			}

			_IsSelected = _IsDown = false;
		}
	};
	_TouchListener->onTouchCancelled = [&](Touch* touch, Event*)
	{
		_IsSelected = _IsDown = _IsChecked = false;
	};
	dispatcher->addEventListenerWithFixedPriority(_TouchListener, 1);

	return true;
}