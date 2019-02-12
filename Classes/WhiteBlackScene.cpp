#include "WhiteBlackScene.h"
#include "SimpleAudioEngine.h"
#include "Hero.h"
#include "SimpleAudioEngine.h"
#include"cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MyCallBackReader.h"
using namespace cocos2d;
using namespace cocostudio::timeline;
USING_NS_CC;
Scene* WhiteBlackScene::createScene()
{
	return WhiteBlackScene::create();
}
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
}
bool WhiteBlackScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			map[i][j] = 0;
		}
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	CSLoader* instance = CSLoader::getInstance();
	instance->registReaderObject("MyCallBackReader", (ObjectFactory::Instance)MyCallBackReader::getInstance);
	Node *m_csbNode = CSLoader::createNode("WhiteBlack.csb");
	m_csbNode->setContentSize(visibleSize);
	ui::Helper::doLayout(m_csbNode);
	this->addChild(m_csbNode);

	this->scheduleUpdate();
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(WhiteBlackScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(WhiteBlackScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	actor = Hero::create("1.png");
	if (actor == nullptr) {
		problemLoading("1.png");
	}
	else {
		actor->init("actor.plist");
		actor->tag = 1;
		actor->setAnchorPoint(Vec2(0.5, 0));
		actor->setPosition(Vec2(185, 600));
		this->addChild(actor, 0);
	}
	star = Hero::create("2.png");
	if (star == nullptr) {
		problemLoading("2.png");
	}
	else {
		star->init("star.plist");
		star->tag = 2;
		star->setAnchorPoint(Vec2(0.5, 0));
		star->setPosition(Vec2(635, 150));
		star->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
		this->addChild(star, 0);
	}
	return true;
}

void WhiteBlackScene::releaseKey(int flag) {
	if (flag == 1) {
		keys[EventKeyboard::KeyCode::KEY_UP_ARROW] = false;
		keys[EventKeyboard::KeyCode::KEY_LEFT_ARROW] = false;
		keys[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = false;
		keys[EventKeyboard::KeyCode::KEY_DOWN_ARROW] = false;
	}
	else if (flag == 2) {
		keys[EventKeyboard::KeyCode::KEY_W] = false;
		keys[EventKeyboard::KeyCode::KEY_A] = false;
		keys[EventKeyboard::KeyCode::KEY_D] = false;
		keys[EventKeyboard::KeyCode::KEY_S] = false; 
	}
}

Vec2 WhiteBlackScene::getXY(Vec2 xy) {
	int x = xy.x;
	int y = xy.y;
	x = abs(x - 185) / 50;
	y = abs(y - 600) / 50;
	return Vec2(y, x);
}

void WhiteBlackScene::boom_finish(CCNode* pTarget, void* boom) {
	Vec2 XY = getXY(((Sprite*)boom)->getPosition());
	int x = (int)XY.x;
	int y = (int)XY.y;
	int n = 3;
	int temp_x = x;
	int temp_y = y;
	int tag = ((Sprite*)boom)->getTag();
	CCLOG("%d,%d", x, y);
	for (int i = 0; i < n; i++) {
		if (temp_x - 1 >= -1) {
			map[temp_x--][temp_y] = tag;
		}
		else {
			break;
		}
	}
	temp_x = x;
	temp_y = y;
	for (int i = 0; i < n; i++) {
		if (temp_x + 1 <= 10) {
			map[temp_x++][temp_y] = tag;
		}
		else {
			break;
		}
	}
	temp_x = x;
	temp_y = y;
	for (int i = 0; i < n; i++) {
		if (temp_y - 1 >= -1) {
			map[temp_x][temp_y--] = tag;
		}
		else {
			break;
		}
	}
	temp_x = x;
	temp_y = y;
	for (int i = 0; i < n; i++) {
		if (temp_y + 1 <= 10) {
			map[temp_x][temp_y++] = tag;
		}
		else {
			break;
		}
	}

	for (int i = 0; i < 10; i++) {
		CCLOG("%d %d %d %d %d %d %d %d %d %d", map[i][0], map[i][1], map[i][2], map[i][3], map[i][4], map[i][5], map[i][6], map[i][7], map[i][8], map[i][9]);
	}
}

void WhiteBlackScene::boom_boom(Sprite* boom) {
	auto scaleTo_s = ScaleTo::create(0.5, 0.5);
	auto scaleTo_b = ScaleTo::create(0.5, 1.0);
	auto mySequence = Sequence::create(scaleTo_s, scaleTo_b, scaleTo_s->clone(), scaleTo_b->clone(), 
									   CCCallFuncND::create(this, callfuncND_selector(WhiteBlackScene::boom_finish), (void*)boom),
									   nullptr);
	boom->runAction(mySequence);
}

void WhiteBlackScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event *event) {
	if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		releaseKey(1);
		keys[keycode] = true;
		actor->move(3);
		actor->state = 3;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		releaseKey(1);
		keys[keycode] = true;
		actor->move(1);
		actor->state = 1;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		releaseKey(1);
		keys[keycode] = true;
		actor->move(2);
		actor->state = 2;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		releaseKey(1);
		keys[keycode] = true;
		actor->move(0);
		actor->state = 0;
	}

	if (keycode == EventKeyboard::KeyCode::KEY_W) {
		releaseKey(2);
		keys[keycode] = true;
		star->move(3);
		star->state = 3;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_A) {
		releaseKey(2);
		keys[keycode] = true;
		star->move(1);
		star->state = 1;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_D) {
		releaseKey(2);
		keys[keycode] = true;
		star->move(2);
		star->state = 2;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_S) {
		releaseKey(2);
		keys[keycode] = true;
		star->move(0);
		star->state = 0;
	}

	if (keycode == EventKeyboard::KeyCode::KEY_SPACE) {
		if (actor->boom > 0) {
			actor->boom--;
			int x = actor->getXY().x;
			int y = actor->getXY().y;
			auto boom_1 = Sprite::create();
			boom_1->initWithFile("w_heart.png");
			boom_1->setPosition(Vec2(185 + 50 * x, 600 - 50 * y));
			boom_1->setTag(1);
			this->addChild(boom_1);
			boom_boom(boom_1);
		}
	}

	if (keycode == EventKeyboard::KeyCode::KEY_ENTER) {
		if (star->boom > 0) {
			star->boom--;
			int x = star->getXY().x;
			int y = star->getXY().y;
			auto boom_2 = Sprite::create();
			boom_2->initWithFile("b_heart.png");
			boom_2->setPosition(Vec2(185 + 50 * x, 600 - 50 * y));
			boom_2->setTag(2);
			this->addChild(boom_2);
			boom_boom(boom_2);
		}
	}
}

void WhiteBlackScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event *event) {
	keys[keycode] = false;
	if ((keycode == EventKeyboard::KeyCode::KEY_UP_ARROW && actor->state==3)
		|| (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW && actor->state == 1)
		|| (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW && actor->state == 2)
		|| (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW && actor->state == 0)) 
	{
		actor->stop();
		actor->state = -1;
	}

	if ((keycode == EventKeyboard::KeyCode::KEY_W && star->state == 3)
		|| (keycode == EventKeyboard::KeyCode::KEY_A && star->state == 1)
		|| (keycode == EventKeyboard::KeyCode::KEY_D && star->state == 2)
		|| (keycode == EventKeyboard::KeyCode::KEY_S && star->state == 0))
	{
		star->stop();
		star->state = -1;
	}
}

bool WhiteBlackScene::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (keys[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}

bool WhiteBlackScene::judge(Vec2 pos, int tag) {
	Vec2 XY = getXY(pos);
	int x = (int)XY.x;
	int y = (int)XY.y;
	CCLOG("%d,%d", x, y);
	if (map[x][y] == tag || map[x][y] == 0) {
		return true;
	}
	return false;
}

void WhiteBlackScene::update(float dt) {
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW)) {
		float x = actor->getPosition().x;
		float y = actor->getPosition().y;
		if (judge(Vec2(x, y - 1), 1) && y >= 150) {
			actor->setPosition(x, y - 1);
		}
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {
		float x = actor->getPosition().x;
		float y = actor->getPosition().y;
		if (judge(Vec2(x - 1, y), 1) && x >= 185) {
			actor->setPosition(x - 1, y);
		}
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
		float x = actor->getPosition().x;
		float y = actor->getPosition().y;
		if (judge(Vec2(x + 1, y), 1) && x <= 635) {
			actor->setPosition(x + 1, y);
		}
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW)) {
		float x = actor->getPosition().x;
		float y = actor->getPosition().y;
		if (judge(Vec2(x, y + 1), 1) && y<= 600) {
			actor->setPosition(x, y + 1);
		}
	}

	if (isKeyPressed(EventKeyboard::KeyCode::KEY_S)) {
		float xx = star->getPosition().x;
		float yy = star->getPosition().y;
		if (judge(Vec2(xx, yy - 1), 2) && yy >= 150) {
			star->setPosition(xx, yy - 1);
		}
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_A)) {
		float xx = star->getPosition().x;
		float yy = star->getPosition().y;
		if (judge(Vec2(xx - 1, yy), 2) && xx >= 185) {
			star->setPosition(xx - 1, yy);
		}
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_D)) {
		float xx = star->getPosition().x;
		float yy = star->getPosition().y;
		if (judge(Vec2(xx + 1, yy), 2) && xx <= 635) {
			star->setPosition(xx + 1, yy);
		}
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_W)) {
		float xx = star->getPosition().x;
		float yy = star->getPosition().y;
		if (judge(Vec2(xx, yy + 1), 2) && yy <= 600) {
			star->setPosition(xx, yy + 1);
		}
	}
}
