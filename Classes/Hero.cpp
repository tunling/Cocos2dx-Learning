#include "Hero.h"
#include "cocos2d.h"
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
void Hero::init(const char* plistFileName) {
	frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile(plistFileName);
	v = 0.1;
	state = -1;
	tag = 0;
	boom = 10;
}
void Hero::move(int faceTo) {
	Animate* animate = nullptr;
	Vector<SpriteFrame*> vec;
	char name[20] = { 0 };
	for (int j = 4 * faceTo + 1; j <= 4 * faceTo + 4; j++) {
		sprintf(name, "%d.png", j);
		vec.pushBack(frameCache->getSpriteFrameByName(name));
	}
	auto animation = Animation::createWithSpriteFrames(vec);
	animation->setDelayPerUnit(v);
	animation->setLoops(-1);
	animate = Animate::create(animation);
	animate->setTag(tag);
	this->getActionManager()->removeActionByTag(tag,this);
	this->runAction(animate);
}

void Hero::stop() {
	this->getActionManager()->removeActionByTag(tag, this);
}

Vec2 Hero::getXY() {
	int x = this->getPosition().x;
	int y = this->getPosition().y;
	int X = abs(x - 185) / 50;
	int Y = abs(y - 600) / 50;
	return Vec2(X, Y);
}