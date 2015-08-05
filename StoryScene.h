//#pragma once
//#include "cocos2d.h"
//#include "cocostudio\CocoStudio.h"
//#include "ui\CocosGUI.h"
//
//class StoryScene : public cocos2d::Layer
//{
//private:
//	virtual bool init();
//
//	bool _NextChapterAble = true;
//	int _CurChapter = 1;
//
//	cocos2d::Action* _Chapter[4];
//
//	cocos2d::Sprite* _Img_Sky_Bg, *_Img_Bg, *_Img_Black;
//	cocos2d::Sprite* _Img_Speech[4];
//
//	cocos2d::EventListenerTouchOneByOne* _TouchListener;
//
//public:
//    static cocos2d::Scene* createScene();
//        
//	CREATE_FUNC(StoryScene);
//
//	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;
//
//	virtual void onExit() override
//	{
//		Layer::onExit();
//		getEventDispatcher()->removeEventListener(_TouchListener);
//		for (int i = 0; i < 4; ++i)
//		{
//			_Chapter[i]->retain();
//		}
//	}
//};
//
