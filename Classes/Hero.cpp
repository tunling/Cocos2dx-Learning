#include "Hero.h"
USING_NS_CC;
Hero* Hero::create(const char* picFileName) {
	Hero* sprite = new Hero();
	if (sprite && sprite->initWithFile(picFileName))
	{
		sprite->autorelease(); 
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
