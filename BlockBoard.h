#pragma once
#include "cocos2d.h"
#include "Block.h"


class BlockBoard
	: public cocos2d::Layer
{
private:
	CC_DISALLOW_COPY_AND_ASSIGN(BlockBoard);
	BlockBoard(int row, int col, int *pScore, float* pTime);
	~BlockBoard();

private:
	const int _BlockRow, _BlockCol;

	//Block* _Block[BLOCK_ROW][BLOCK_COL];
	Block*** _Block;
	Block* _SelBlock;

	cocos2d::Sprite** _LineBox;

	int _SelRow, _SelCol;

	float _stdScaleSize;

	bool *_LineClear;
	bool _Clear;

	void SetAllBlocksColor();
	bool CheckLine(int lineNum);

	int* _pScore;
	float* _pTime;

	cocos2d::EventListenerTouchOneByOne* _TouchListener;

public:
	static BlockBoard* create(int row, int col, int *pScore, float* pTime)
	{
		auto node = new BlockBoard(row, col, pScore, pTime);
		if (node && node->init())
		{
			return node;
		}
		else
		{
			delete node;
			return nullptr;
		}
	}

	virtual bool init() override;
	void Update();
	virtual void onExit() override;

	void CheckBlocks();

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) override;
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) override;
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event) override;

	void PauseWithChild();
	void ResumeWithChild();

	bool IsClear() { return _Clear; }
};

