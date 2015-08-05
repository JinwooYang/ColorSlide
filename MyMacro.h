#pragma once

// * Scene을 만들때 사용하는 매크로 함수
// * create 함수가 정의되어 있어야 함
#define CREATE_SCENE_FUNC(__TYPE__)\
	static cocos2d::Scene* createScene()\
	{\
		auto scene = cocos2d::Scene::create();\
		auto layer = __TYPE__::create();\
		scene->addChild(layer);\
		return scene;\
	}