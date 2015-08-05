//#include "storyScene.h"
//#include "TitleScene.h"
//
//USING_NS_CC;
//
//Scene* StoryScene::createScene()
//{
//    auto scene = Scene::create();
//    
//	auto layer = StoryScene::create();
//
//    scene->addChild(layer);
//
//    return scene;
//}
//
//bool StoryScene::init()
//{
//    if ( !Layer::init() )
//    {
//        return false;
//    }
//
//
//	auto csb = CSLoader::createNode("storyScene.csb");
//	this->addChild(csb);
//
//	_Img_Sky_Bg = (Sprite*)csb->getChildByName("img_sky_bg");
//	_Img_Bg = (Sprite*)csb->getChildByName("img_bg");
//	_Img_Black = (Sprite*)csb->getChildByName("img_black_alpha_1");
//
//	for (int i = 0; i < 4; ++i)
//	{
//		_Img_Speech[i] = Sprite::create(String::createWithFormat("ColorSlideResources/StoryScene/img_text_%d.png", i + 1)->getCString());
//		_Img_Speech[i]->setPosition(360, 991);
//		_Img_Speech[i]->setVisible(false);
//		this->addChild(_Img_Speech[i]);
//	}
//
//	csb->setPosition(-720.0f, 0.0f);
//	_Img_Speech[0]->setVisible(true);
//
//
//	auto nextChapterAble = [&]()
//	{
//		_NextChapterAble = true;
//	};
//
//	auto chapter1 = [=]()
//	{
//		csb->setPosition(-720.0f, 0.0f);
//		_Img_Speech[0]->setVisible(true);
//	};
//
//	auto chapter2 = [=]()
//	{
//		_Img_Speech[0]->setVisible(false);
//		_Img_Speech[1]->setVisible(true);
//	};
//
//	auto chapter3 = [=]()
//	{
//		auto seq = Sequence::create(MoveTo::create(1.5f, Vec2::ZERO), CallFunc::create([&]()
//		{		
//			_Img_Speech[1]->setVisible(false);
//			_Img_Speech[2]->setVisible(true);
//		}));
//		csb->runAction(seq);
//	};
//
//	auto chapter4 = [=]()
//	{
//		auto seq = Sequence::create(MoveTo::create(1.5f, Vec2(-720.0f, 0.0f)), CallFunc::create([&]()
//		{
//			_Img_Speech[2]->setVisible(false);
//			_Img_Speech[3]->setVisible(true);
//		}));
//		csb->runAction(seq);
//	};
//
//
//	_Chapter[0] = Sequence::create(CallFunc::create(chapter1), DelayTime::create(1.5f), CallFunc::create(nextChapterAble), nullptr);
//	_Chapter[1] = Sequence::create(CallFunc::create(chapter2), DelayTime::create(1.5f), CallFunc::create(nextChapterAble), nullptr);
//	_Chapter[2] = Sequence::create(CallFunc::create(chapter3), CallFunc::create(nextChapterAble), nullptr);
//	_Chapter[3] = Sequence::create(CallFunc::create(chapter4), CallFunc::create(nextChapterAble), CallFunc::create([]()
//	{				
//		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, TitleScene::createScene()));
//	}), nullptr);
//
//	for (int i = 0; i < 4; ++i)
//	{
//		_Chapter[i]->retain();
//	}
//
//	_TouchListener = EventListenerTouchOneByOne::create();
//	_TouchListener->onTouchBegan = [&](Touch* touch, Event* event)->bool
//	{
//		this->onTouchBegan(touch, event);
//		return true;
//	};
//	getEventDispatcher()->addEventListenerWithSceneGraphPriority(_TouchListener, this);
//
//    return true;
//}
//
//bool StoryScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
//{
//	if (_NextChapterAble && _CurChapter < 4)
//	{
//		_NextChapterAble = false;
//		this->runAction(_Chapter[_CurChapter++]);
//	}
//	return true;
//}
