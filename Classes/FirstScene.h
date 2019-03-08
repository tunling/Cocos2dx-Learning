#ifndef __FIRST_SCENE_H__
#define __FIRST_SCENE_H__
#include "cocos2d.h"
#include "Hero.h"
USING_NS_CC;
class FirstScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
	bool FirstScene::isKeyPressed(EventKeyboard::KeyCode keyCode);
	CREATE_FUNC(FirstScene);
	virtual void update(float dt);
private:
	Hero* actor;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
};
#endif // ! __FIRST_SCENE_H__
