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
	this->scheduleUpdate();
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(FirstScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(FirstScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	actor = Hero::create("1.png");
	actor->init("actor.plist");
	if (actor == nullptr) {
		problemLoading("1.png");
	}
	else {
		actor->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
		this->addChild(actor, 0);
	}
	return true;
}

void FirstScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event *event) {
	keys[keycode] = true;
	if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		actor->move(3);
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		actor->move(1);
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		actor->move(2);
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		actor->move(0);
	}
}

void FirstScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event *event) {
	keys[keycode] = false;
	if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW || keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW 
		|| keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		actor->stop();
	}
}

bool FirstScene::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (keys[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}

void FirstScene::update(float dt) {
	float x = actor->getPosition().x;
	float y = actor->getPosition().y;
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW)) {
		actor->setPosition(x, y - 1);
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {
		actor->setPosition(x - 1, y);
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
		actor->setPosition(x + 1, y);
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW)) {
		actor->setPosition(x, y + 1);
	}
}
