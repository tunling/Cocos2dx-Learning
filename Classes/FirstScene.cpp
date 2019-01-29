#include "FirstScene.h"
#include "SimpleAudioEngine.h"
#include "Hero.h"
USING_NS_CC;
Scene* FirstScene::createScene()
{
	return FirstScene::create();
}
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
}
bool FirstScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto colorLayer = CCLayerColor::create();
	colorLayer->initWithColor(ccc4(0, 100, 100, 150));
	this->addChild(colorLayer, -1);
	auto actor = Hero::create("Actor.png");
	if (actor == nullptr) {
		problemLoading("Actor.png");
	}
	else {
		actor->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
		actor->setScale(0.5);
		this->addChild(actor, 0);
	}
	return true;
}
