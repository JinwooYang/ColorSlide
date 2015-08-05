#pragma once

// * Scene�� ���鶧 ����ϴ� ��ũ�� �Լ�
// * create �Լ��� ���ǵǾ� �־�� ��
#define CREATE_SCENE_FUNC(__TYPE__)\
	static cocos2d::Scene* createScene()\
	{\
		auto scene = cocos2d::Scene::create();\
		auto layer = __TYPE__::create();\
		scene->addChild(layer);\
		return scene;\
	}