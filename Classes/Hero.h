#ifndef __Hero__
#define __Hero__
#include "cocos2d.h"
using namespace std;
USING_NS_CC;
class Hero : public cocos2d::Sprite
{
public:
	static Hero* create(const char* picFileName);
	void move(int faceTo);
	void stop();
	void init(const char* plistFileName);
	int state;
private:
protected:
	SpriteFrameCache* frameCache;
	float v;
};
#endif // !Hero


