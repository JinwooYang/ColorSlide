#include "Block.h"

USING_NS_CC;

int scoreTable[5] = {350, 500, 750, 850, 1000};

Block::Block()
{
}


Block::~Block()
{
}

bool Block::init()
{
	//this->initWithFile(R"(images/block.jpg)");
	//this->initWithFile(R"(ColorSlideResources/gameScene/game_btn_diamond.png)");
	//this->getTexture()->setAntiAliasTexParameters();
	//this->getTexture()->setAliasTexParameters();
	_MoveAble = true;
	_Selected = false;
	return true;
}

void Block::Select()
{
	_Selected = true;
	_SelectedImg = Sprite::create(g_BlockSelectedImg[_Color]);
	_SelectedImg->setPosition(this->getPosition());
	_SelectedImg->setScale(this->getScale());
	this->getParent()->addChild(_SelectedImg, this->getLocalZOrder() + 1);
}

void Block::DeSelect()
{
	_Selected = false;
	if (_SelectedImg)
	{
		this->getParent()->removeChild(_SelectedImg, true);
		_SelectedImg = nullptr;
	}
}

int Block::GetScore()
{
	return scoreTable[_Color];
}