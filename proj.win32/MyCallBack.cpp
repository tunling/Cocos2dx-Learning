#include "MyCallBack.h" 
#include "ui/UIText.h" 
#include "WhiteBlackScene.h"
#include "MenuScene.h"
USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;

MyCallBack::MyCallBack()
{}

Widget::ccWidgetTouchCallback MyCallBack::onLocateTouchCallback(const string &callBackName)
{
	if (callBackName == "onTouch")
	{
		return CC_CALLBACK_2(MyCallBack::onTouch, this);
	}
	return nullptr;
}

Widget::ccWidgetClickCallback MyCallBack::onLocateClickCallback(const string &callBackName)
{
	if (callBackName == "onClick")
	{
		return CC_CALLBACK_1(MyCallBack::onClick, this);
	}
	else if (callBackName == "click_start") {
		return CC_CALLBACK_1(MyCallBack::click_start, this);
	}
	else if (callBackName == "click_end") {
		return CC_CALLBACK_1(MyCallBack::click_end, this);
	}
	else if (callBackName == "restart") {
		return CC_CALLBACK_1(MyCallBack::restart, this);
	}
	else if (callBackName == "menu") {
		return CC_CALLBACK_1(MyCallBack::menu, this);
	}
	return nullptr;
}

Widget::ccWidgetEventCallback MyCallBack::onLocateEventCallback(const string &callBackName)
{
	if (callBackName == "onEvent")
	{
		return CC_CALLBACK_2(MyCallBack::onEvent, this);
	}
	return nullptr;
}
void MyCallBack::restart(cocos2d::Ref* sender)
{
	Director::getInstance()->end();
}

void MyCallBack::menu(cocos2d::Ref* sender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, MenuScene::create(), Color3B(0, 100, 100)));
}
void MyCallBack::click_start(cocos2d::Ref* sender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, WhiteBlackScene::create(), Color3B(0, 100, 100)));
}

void MyCallBack::click_end(cocos2d::Ref* sender)
{
	Director::getInstance()->end();
}
void MyCallBack::onTouch(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
	CCLOG("onTouch");
}

void MyCallBack::onClick(cocos2d::Ref* sender)
{
	CCLOG("onClick");
}

void MyCallBack::onEvent(cocos2d::Ref* sender, int eventType)
{
	CCLOG("onEvent");
}