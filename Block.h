#pragma once
#include "cocos2d.h"
#include "UserDefines.h"

static char* g_BlockImg[5] = { R"(ColorSlideResources/gameScene/img_green.png)",
								R"(ColorSlideResources/gameScene/img_red.png)",
								R"(ColorSlideResources/gameScene/img_yellow.png)",
								R"(ColorSlideResources/gameScene/img_purple.png)",
								R"(ColorSlideResources/gameScene/img_blue.png)"};

static char* g_BlockSelectedImg[5] = { R"(ColorSlideResources/gameScene/img_green_select.png)",
										R"(ColorSlideResources/gameScene/img_red_select.png)",
										R"(ColorSlideResources/gameScene/img_yellow_select.png)",
										R"(ColorSlideResources/gameScene/img_purple_select.png)",
										R"(ColorSlideResources/gameScene/img_blue_select.png)" };


class Block
	: public cocos2d::Sprite
{
private:
	CC_DISALLOW_COPY_AND_ASSIGN(Block);
	Block();
	~Block();

private:
	int _Color;
	bool _MoveAble;
	bool _Selected;
	cocos2d::Sprite* _SelectedImg;

public:
	CREATE_FUNC(Block);

	virtual bool init() override;

	void SetEnumColor(int color)
	{
		_Color = color;
		this->initWithFile(g_BlockImg[_Color]);
	}

	void SetScale(float scale)
	{
		Sprite::setScale(scale);
		_SelectedImg->setScale(scale);
	}

	void Select();

	void DeSelect();

	int GetEnumColor() { return _Color; }

	void SetMoveAble(bool able) { _MoveAble = able; }
	bool IsMoveAble() { return _MoveAble; }

	int GetScore();
};

