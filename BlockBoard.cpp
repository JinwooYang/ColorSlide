#include "BlockBoard.h"
#include "UserDefines.h"
#include "AudioEngine.h"
#include "SoundManager.h"

USING_NS_CC;

const char* cBlockScoreImg[5] = { R"(ColorSlideResources/gameScene/img_green_score.png)",
									R"(ColorSlideResources/gameScene/img_red_score.png)",
									R"(ColorSlideResources/gameScene/img_yellow_score.png)",
									R"(ColorSlideResources/gameScene/img_purple_score.png)",
									R"(ColorSlideResources/gameScene/img_blue_score.png)"};


BlockBoard::BlockBoard(int row, int col, int* pScore, float* pTime) :
_BlockRow(row),
_BlockCol(col),
_pScore(pScore),
_pTime(pTime)
{
	_Block = new Block**[_BlockRow];

	for (int i = 0; i < _BlockCol; ++i)
	{
		_Block[i] = new Block*[_BlockCol];
	}

	_LineBox = new Sprite*[_BlockRow];
	_LineClear = new bool[_BlockRow];
}


BlockBoard::~BlockBoard()
{
	for (int i = 0; i < _BlockCol; ++i)
	{
		delete[] _Block[i];
	}

	delete[] _Block;
	delete[] _LineBox;
	delete[] _LineClear;
}


void BlockBoard::SetAllBlocksColor()
{
	int randNum = 0;

	int *colorNumArr = new int[_BlockRow];

	for (int i = 0; i < _BlockRow; ++i)
	{
		colorNumArr[i] = 0;
	}

	for (int i = 0; i < _BlockCol * _BlockRow; ++i)
	{
		int row = i / _BlockCol;
		int col = i % _BlockCol;

		do
		{
			randNum = cocos2d::random(0, _BlockRow - 1);
		} while ((++colorNumArr[randNum]) > _BlockCol);

		_Block[row][col]->SetEnumColor(randNum);
		//_Block[row][col]->setColor(cBlockColor[randNum]);
	}

	for (int i = 0; i < _BlockRow; ++i)
	{
		if (CheckLine(i))
		{
			SetAllBlocksColor();
			break;
		}
	}

	delete []colorNumArr;
}
bool BlockBoard::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//일반 멤버 초기화
	_SelBlock = nullptr;
	_SelRow = _SelCol = 0;

	_Clear = false;

	for (int i = 0; i < _BlockRow; ++i)
	{
		_LineClear[i] = false;
		_LineBox[i] = nullptr;
	}


	//블럭 초기화
	auto winSize = Director::getInstance()->getVisibleSize();
	Size blockSize = Size(winSize.width / _BlockCol, winSize.width / _BlockCol);

	this->setPositionY(140);


	for (int i = 0; i < _BlockCol * _BlockRow; ++i)
	{
		int row = i / _BlockCol;
		int col = i % _BlockCol;

		_Block[row][col] = Block::create();
	}

	SetAllBlocksColor();

	for (int i = 0; i < _BlockCol * _BlockRow; ++i)
	{
		int row = i / _BlockCol;
		int col = i % _BlockCol;


		auto curBlock = _Block[row][col];
		curBlock->setPosition(col * blockSize.width + (blockSize.width / 2), row * blockSize.height + (blockSize.height / 2));
		this->addChild(curBlock);

		if (i == 0)
		{
			auto box = curBlock->getBoundingBox();
			_stdScaleSize = blockSize.width / box.getMaxX();
			_stdScaleSize -= 0.1;
		}
		curBlock->setScale(_stdScaleSize);
	}


	//Add Listener
	_TouchListener = EventListenerTouchOneByOne::create();
	_TouchListener->onTouchBegan = [&](Touch* touch, Event* event)->bool
	{
		this->onTouchBegan(touch, event);
		return true;
	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(_TouchListener, this);

	return true;
}

bool BlockBoard::CheckLine(int LineNum)
{
	bool checkClear = true;

	if (!_LineClear[LineNum])
	{
		int compareColor = _Block[LineNum][0]->GetEnumColor();
		for (int j = 1; j < _BlockCol; ++j)
		{
			if (compareColor != _Block[LineNum][j]->GetEnumColor())
			{
				checkClear = false;
			}
		}
		if (checkClear)
		{
			return true;
		}
	}

	return false;
}

void BlockBoard::CheckBlocks()
{
	//클리어된 라인이 있는지 체크
	for (int i = 0; i < _BlockRow; ++i)
	{
		if (CheckLine(i))
		{
			log("%d line Clear!", i + 1);
					
			auto winSize = Director::getInstance()->getWinSize();
			auto color = Color4B(cBlockColor[_Block[i][0]->GetEnumColor()]);
			auto blockRect = _Block[i][0]->getBoundingBox();			
			
			if (!_LineBox[i])
			{
				_LineBox[i] = Sprite::create("ColorSlideResources/gameScene/game_img_checkbox.png");
				_LineBox[i]->setPosition(0, blockRect.getMidY());
				_LineBox[i]->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
				_LineBox[i]->setColor(cBlockColor[_Block[i][0]->GetEnumColor()]);
				_LineBox[i]->setOpacity(228);
				_LineBox[i]->setScaleY(_stdScaleSize - 0.1);
				_LineBox[i]->runAction(Sequence::create(EaseInOut::create(MoveTo::create(0.3f, Vec2(winSize.width, _LineBox[i]->getPositionY())), 5.0f),
					CallFunc::create([=]()
				{
					SoundManager::PlaySFX("sfx/cash.mp3");

					auto check = Sprite::create(cBlockScoreImg[_Block[i][0]->GetEnumColor()]);
					auto orgSize = check->getTextureRect().size;
					check->setPosition((winSize.width / 2) - (orgSize.width / 2), _LineBox[i]->getPositionY());
					check->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
					check->setTextureRect(Rect::ZERO);
					check->runAction(RepeatForever::create(Sequence::create(CallFunc::create([=]()
					{
						auto curSize = check->getTextureRect().size;
						if (curSize.width < orgSize.width)
						{
							check->setTextureRect(Rect(0, 0, curSize.width + 20, orgSize.height));
						}
						else
						{
							check->setTextureRect(Rect(0, 0, orgSize.width, orgSize.height));
							_LineClear[i] = true;
							check->stopAllActions();
						}
					}), nullptr)));
					this->addChild(check);
				}), nullptr));
				this->addChild(_LineBox[i]);
			}

			//_LineClear[i] = true;
			*_pTime += 1.0f;
			*_pScore += _Block[i][0]->GetScore();

			for (int j = 0; j < _BlockCol; ++j)
			{
				_Block[i][j]->SetMoveAble(false);
			}
		}
	}
}

void BlockBoard::Update()
{
	//라인이 전부 클리어되지 않았으면 리턴
	for (int i = 0; i < _BlockRow; ++i)
	{
		if (!_LineClear[i])
			return;
	}


	//모든 블럭들의 애니메이션이 끝나지않았으면 리턴
	for (int i = 0; i < _BlockCol * _BlockRow; ++i)
	{
		int row = i / _BlockCol;
		int col = i % _BlockCol;
		if (_Block[row][col]->getNumberOfRunningActions() > 0)
		{
			return;
		}
	}

	log("Block Clear!");
	*_pScore += 2000;
	*_pTime += 2.0f;
	_Clear = true;
}

void BlockBoard::onExit()
{
	Layer::onExit();
	getEventDispatcher()->removeEventListener(_TouchListener);
}

bool BlockBoard::onTouchBegan(Touch* touch, Event* event)
{
	for (int i = 0; i < _BlockCol * _BlockRow; ++i)
	{
		int row = i / _BlockCol;
		int col = i % _BlockCol;

		auto touchPos = touch->getLocation() - getPosition();
		auto curBlock = _Block[row][col];

		if (curBlock->IsMoveAble() && curBlock->getBoundingBox().containsPoint(touchPos))
		{

			if (!_SelBlock)
			{
				if (curBlock->getNumberOfRunningActions() == 0)
				{
					curBlock->runAction(EaseElasticOut::create(ScaleTo::create(0.3f, _stdScaleSize + 0.1f), 0.45f));
					curBlock->setLocalZOrder(2);
					_SelBlock = curBlock;
					_SelBlock->Select();
					SoundManager::PlaySFX("sfx/jewel_push.mp3");
					_SelRow = row;
					_SelCol = col;
				}
			}
			else if (_SelBlock == curBlock)
			{
				_SelBlock->DeSelect();
				SoundManager::PlaySFX("sfx/jewel_pop.mp3");
				_SelBlock->runAction(ScaleTo::create(0.15f, _stdScaleSize));
				_SelBlock->setLocalZOrder(0);
				_SelBlock = nullptr;
				break;
			}
			else if (row == _SelRow || col == _SelCol)
			{
				if (curBlock->getNumberOfRunningActions() > 0) break;

				curBlock->setLocalZOrder(1);
				_SelBlock->setLocalZOrder(0);

				float speed = 0.09f;

				auto move = MoveTo::create(speed, _SelBlock->getPosition());
				auto scale = ScaleTo::create(speed, _stdScaleSize + 0.1f);

				curBlock->runAction(Sequence::create(
					ScaleTo::create(speed, _stdScaleSize + 0.1f),
					MoveTo::create(speed, _SelBlock->getPosition()),
					ScaleTo::create(speed, _stdScaleSize),
					CallFunc::create(std::bind([&](Block* block)
					{
						block->setLocalZOrder(0);
						this->CheckBlocks();
					}, curBlock)), nullptr));

				_SelBlock->runAction(Sequence::create(
					DelayTime::create(speed),
					MoveTo::create(speed, curBlock->getPosition()),
					ScaleTo::create(speed, _stdScaleSize), nullptr));

				auto tempBlock = _Block[row][col];
				_Block[row][col] = _SelBlock;
				_Block[_SelRow][_SelCol] = tempBlock;

				_SelBlock->DeSelect();
				SoundManager::PlaySFX("sfx/jewel_pop.mp3");
				_SelBlock = nullptr;
				break;
			}
		}
	}

	return true;
}

void BlockBoard::onTouchMoved(Touch* touch, Event* event)
{
}

void BlockBoard::onTouchEnded(Touch* touch, Event* event)
{
}

void BlockBoard::onTouchCancelled(Touch* touch, Event* event)
{
}

void BlockBoard::PauseWithChild()
{
	_TouchListener->setEnabled(false);
	this->pause();

	for (auto child : _children)
	{
		child->pause();
	}
}

void BlockBoard::ResumeWithChild()
{
	_TouchListener->setEnabled(true);
	this->resume();

	for (auto child : _children)
	{
		child->resume();
	}
}