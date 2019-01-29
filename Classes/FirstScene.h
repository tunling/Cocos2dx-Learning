#ifndef __FIRST_SCENE_H__
#define __FIRST_SCENE_H__
#include "cocos2d.h"
class FirstScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(FirstScene);
};
#endif // ! __FIRST_SCENE_H__
