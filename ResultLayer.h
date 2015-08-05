#pragma once
#include "cocos2d.h"
#include "MyMacro.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

class ResultLayer
	: public cocos2d::Layer
{
private:
	CC_DISALLOW_COPY_AND_ASSIGN(ResultLayer);
	ResultLayer();
	~ResultLayer();

private:
	int _Score, _PlayTime;

	cocos2d::Sprite* _Img_BlackAlpha;
	cocos2d::Sprite* _Img_Center;
	cocos2d::Sprite* _Img_Bankruptcy;
	cocos2d::ui::Text* _Val_Total, *_Val_PlayTime;
	cocos2d::ui::Button* _Btn_Retry, *_Btn_GoHome;

public:
	//CREATE_FUNC(ResultScene);
	//CREATE_SCENE_FUNC(ResultScene);

	static ResultLayer* create(int score, int playTime)
	{
		auto node = new ResultLayer;
		node->autorelease();
		node->_Score = score;
		node->_PlayTime = playTime;

		if (!node->init())
		{
			delete node;
			node = nullptr;
		}

		return node;
	}

	//static cocos2d::Scene* createScene(int score)
	//{
	//	auto scene = cocos2d::Scene::create();
	//	auto layer = ResultLayer::create(score);
	//	scene->addChild(layer);
	//	return scene;
	//}

	virtual bool init() override;
};

