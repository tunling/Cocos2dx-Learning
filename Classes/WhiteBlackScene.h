#ifndef __WB_SCENE_H__
#define __WB_SCENE_H__
#include "cocos2d.h"
#include "Hero.h"
USING_NS_CC;
class WhiteBlackScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	void releaseKey(int flag);
	void boom_boom(Sprite* boom, int tag, Vec2 XY);
	CREATE_FUNC(WhiteBlackScene);
	virtual void update(float dt);
private:
	Hero* actor;
	Hero* star;
	int map[10][10];
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
};
#endif // ! __FIRST_SCENE_H__
