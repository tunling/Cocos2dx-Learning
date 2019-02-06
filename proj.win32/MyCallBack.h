#ifndef __MyCallBack__ 
#define __MyCallBack__ 
#include"cocos2d.h" 
#include"cocostudio/CocoStudio.h"
#include"cocostudio/WidgetCallBackHandlerProtocol.h" 
class MyCallBack : public cocos2d::Node, public cocostudio::WidgetCallBackHandlerProtocol
{
public:
	CREATE_FUNC(MyCallBack)
	MyCallBack();
	virtual cocos2d::ui::Widget::ccWidgetTouchCallback onLocateTouchCallback(const std::string &callBackName);
	virtual cocos2d::ui::Widget::ccWidgetClickCallback onLocateClickCallback(const std::string &callBackName);
	virtual cocos2d::ui::Widget::ccWidgetEventCallback onLocateEventCallback(const std::string &callBackName);
	void click_start(cocos2d::Ref* sender);
	void click_end(cocos2d::Ref* sender);
	void onTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void onClick(cocos2d::Ref* sender);
	void onEvent(cocos2d::Ref* sender, int eventType);
private:
	std::vector<std::string> _touchTypes;
	std::string _click;
	std::vector<std::string> _eventTypes;
};
#endif

