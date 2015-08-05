#pragma once
#include "cocos2d.h"

class MyCheckBox
	: public cocos2d::Sprite
{
private:
	CC_DISALLOW_COPY_AND_ASSIGN(MyCheckBox);

	virtual bool init() override;

	bool _IsSelected = false;
	bool _IsChecked = true;

	bool _IsDown = false;

	std::function<void(bool)> _CheckEventCallBack = nullptr;

	cocos2d::EventListenerTouchOneByOne* _TouchListener;

public:
	CREATE_FUNC(MyCheckBox);

	MyCheckBox();
	~MyCheckBox();

	void SetCheck(bool check);
	bool IsChecked() { return _IsChecked; };

	void SetCheckEventCallBack(std::function<void(bool)> checkEventCallBack)
	{
		_CheckEventCallBack = checkEventCallBack;
	};
};

