#include "WhiteBlackScene.h"
#include "SimpleAudioEngine.h"
#include "Hero.h"
#include "SimpleAudioEngine.h"
#include"cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MyCallBackReader.h"
#include "MenuScene.h"
using namespace cocos2d;
using namespace cocostudio::timeline;
USING_NS_CC;
Scene* WhiteBlackScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto whiteBlackScene = WhiteBlackScene::create();
	whiteBlackScene->setPhyWorld(scene->getPhysicsWorld());
	scene->addChild(whiteBlackScene);
	return scene;
}
void WhiteBlackScene::gameover(int tag)
{
	if (!end) {
		char *str;
		if (tag == 1) {
			str = "swin.png";
		}
		else if (tag == 2) {
			str = "awin.png";
		}
		auto win = Sprite::create();
		win->setGlobalZOrder(1000);
		win->initWithFile(str);
		win->setPosition(Vec2(1024 / 2, 768 / 2));
		this->addChild(win);
		auto scaleTo_s = ScaleTo::create(0.5, 0.5);
		auto scaleTo_b = ScaleTo::create(0.5, 1.0);
		auto mySequence = Sequence::create(scaleTo_s, scaleTo_b, scaleTo_s->clone(), scaleTo_b->clone(),
			CCDelayTime::create(3),
			CCCallFuncND::create(this, callfuncND_selector(WhiteBlackScene::endgame), (void*)this),
			nullptr);
		win->runAction(mySequence);
		end = true;
	}
}
void WhiteBlackScene::contact()
{
	EventListenerPhysicsContact* evContact = EventListenerPhysicsContact::create();
	evContact->onContactBegin = [&](PhysicsContact& contact) {
		int tag1 = contact.getShapeA()->getBody()->getNode()->getTag();
		int tag2 = contact.getShapeB()->getBody()->getNode()->getTag();
		if (tag1 == -1) {
			if (tag2 != -1) {
				gameover(tag2);
			}
		}
		return true; 
	};
	evContact->onContactSeparate = [&](PhysicsContact& contact)
	{
		
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(evContact, this);
}
bool WhiteBlackScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	end = false;
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
	auto physicsBody = PhysicsBody::createBox(Size(32.0f, 48.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setCategoryBitmask(0xffff0000);
	physicsBody->setContactTestBitmask(0xffffffff);
	physicsBody->setCollisionBitmask(0xffff0000);
	actor->setPhysicsBody(physicsBody);
	actor->init("actor.plist");
	actor->setTag(1);
	actor->setAnchorPoint(Vec2(0.5, 0));
	actor->setPosition(Vec2(185, 600));
	actor->setGlobalZOrder(10);
	this->addChild(actor, 0);

	star = Hero::create("2.png");
	auto physicsBody = PhysicsBody::createBox(Size(32.0f, 48.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setCategoryBitmask(0x0000ffff);
	physicsBody->setContactTestBitmask(0xffffffff);
	physicsBody->setCollisionBitmask(0x0000ffff);
	star->setPhysicsBody(physicsBody);
	star->init("star.plist");
	star->setTag(2);
	star->setAnchorPoint(Vec2(0.5, 0));
	star->setPosition(Vec2(635, 150));
	star->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	star->setGlobalZOrder(10);
	this->addChild(star, 0);

	contact();
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

void WhiteBlackScene::boom_finish(CCNode* pTarget, void* boom) {
	float x = ((Sprite*)boom)->getPosition().x;
	float y = ((Sprite*)boom)->getPosition().y;
	int n = 4;
	auto boom_boom = Sprite::create();
	boom_boom->initWithFile("boom_boom.png");
	auto physicsBody = PhysicsBody::createBox(Size(50.0f, 50.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setCategoryBitmask(0xffffffff);
	physicsBody->setContactTestBitmask(0xffffffff);
	physicsBody->setCollisionBitmask(0xffffffff);
	boom_boom->setPhysicsBody(physicsBody);
	boom_boom->setPosition(Vec2(25, 25));
	((Sprite*)boom)->addChild(boom_boom);
	for (int i = 1; i < n; i++) {
		auto boom_boom_up = Sprite::create();
		boom_boom_up->initWithFile("up_down.png");
		auto physicsBody1 = PhysicsBody::createBox(Size(50.0f, 50.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
		physicsBody1->setDynamic(false);
		physicsBody1->setCategoryBitmask(0xffffffff);
		physicsBody1->setContactTestBitmask(0xffffffff);
		physicsBody1->setCollisionBitmask(0xffffffff);
		boom_boom_up->setPhysicsBody(physicsBody1);
		boom_boom_up->setPosition(Vec2(25, 50 * i + 25));
		((Sprite*)boom)->addChild(boom_boom_up);

		auto boom_boom_down = Sprite::create();
		boom_boom_down->initWithFile("up_down.png");
		auto physicsBody2 = PhysicsBody::createBox(Size(50.0f, 50.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
		physicsBody2->setDynamic(false);
		physicsBody2->setCategoryBitmask(0xffffffff);
		physicsBody2->setContactTestBitmask(0xffffffff);
		physicsBody2->setCollisionBitmask(0xffffffff);
		boom_boom_down->setPhysicsBody(physicsBody2);
		boom_boom_down->setPosition(Vec2(25, (-50) * i + 25));
		((Sprite*)boom)->addChild(boom_boom_down);

		auto boom_boom_right = Sprite::create();
		boom_boom_right->initWithFile("right_left.png");
		auto physicsBody3 = PhysicsBody::createBox(Size(50.0f, 50.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
		physicsBody3->setDynamic(false);
		physicsBody3->setCategoryBitmask(0xffffffff);
		physicsBody3->setContactTestBitmask(0xffffffff);
		physicsBody3->setCollisionBitmask(0xffffffff);
		boom_boom_right->setPhysicsBody(physicsBody3);
		boom_boom_right->setPosition(Vec2(50 * i + 25, 25));
		((Sprite*)boom)->addChild(boom_boom_right);

		auto boom_boom_left = Sprite::create();
		boom_boom_left->initWithFile("right_left.png");
		auto physicsBody4 = PhysicsBody::createBox(Size(50.0f, 50.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
		physicsBody4->setDynamic(false);
		physicsBody4->setCategoryBitmask(0xffffffff);
		physicsBody4->setContactTestBitmask(0xffffffff);
		physicsBody4->setCollisionBitmask(0xffffffff);
		boom_boom_left->setPhysicsBody(physicsBody4);
		boom_boom_left->setPosition(Vec2((-50) * i + 25, 25));
		((Sprite*)boom)->addChild(boom_boom_left);
	}
}
void WhiteBlackScene::boom_end(CCNode* pTarget, void* boom) {
	float x = ((Sprite*)boom)->getPosition().x;
	float y = ((Sprite*)boom)->getPosition().y;
	int n = 4;
	char *str;
	int tag;
	if (((Sprite*)boom)->getTag() == 1) {
		str = "white.png";
		tag = 0x0000ffff;
	}
	else if (((Sprite*)boom)->getTag() == 2) {
		str = "dark.png";
		tag = 0xffff0000;
	}
	auto boom_boom = Sprite::create();
	boom_boom->initWithFile(str);
	auto physicsBody = PhysicsBody::createBox(Size(50.0f, 50.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setCategoryBitmask(tag);
	boom_boom->setPhysicsBody(physicsBody);
	boom_boom->setPosition(Vec2(x, y));
	this->addChild(boom_boom);
	for (int i = 1; i < n; i++) {
		auto boom_boom_up = Sprite::create();
		boom_boom_up->initWithFile(str);
		auto physicsBody1 = PhysicsBody::createBox(Size(50.0f, 50.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
		physicsBody1->setDynamic(false);
		physicsBody1->setCategoryBitmask(tag);
		physicsBody1->setContactTestBitmask(0);
		physicsBody1->setCollisionBitmask(0xffffffff);
		boom_boom_up->setPhysicsBody(physicsBody1);
		boom_boom_up->setPosition(Vec2(25, 50 * i + 25));
		boom_boom->addChild(boom_boom_up);

		auto boom_boom_down = Sprite::create();
		boom_boom_down->initWithFile(str);
		auto physicsBody2 = PhysicsBody::createBox(Size(50.0f, 50.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
		physicsBody2->setDynamic(false);
		physicsBody2->setCategoryBitmask(tag);
		physicsBody2->setContactTestBitmask(0);
		physicsBody2->setCollisionBitmask(0xffffffff);
		boom_boom_down->setPhysicsBody(physicsBody2);
		boom_boom_down->setPosition(Vec2(25, (-50) * i + 25));
		boom_boom->addChild(boom_boom_down);

		auto boom_boom_right = Sprite::create();
		boom_boom_right->initWithFile(str);
		auto physicsBody3 = PhysicsBody::createBox(Size(50.0f, 50.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
		physicsBody3->setDynamic(false);
		physicsBody3->setCategoryBitmask(tag);
		physicsBody3->setContactTestBitmask(0);
		physicsBody3->setCollisionBitmask(0xffffffff);
		boom_boom_right->setPhysicsBody(physicsBody3);
		boom_boom_right->setPosition(Vec2(50 * i + 25, 25));
		boom_boom->addChild(boom_boom_right);

		auto boom_boom_left = Sprite::create();
		boom_boom_left->initWithFile(str);
		auto physicsBody4 = PhysicsBody::createBox(Size(50.0f, 50.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
		physicsBody4->setDynamic(false);
		physicsBody4->setCategoryBitmask(tag);
		physicsBody4->setContactTestBitmask(0);
		physicsBody4->setCollisionBitmask(0xffffffff);
		boom_boom_left->setPhysicsBody(physicsBody4);
		boom_boom_left->setPosition(Vec2((-50) * i + 25, 25));
		boom_boom->addChild(boom_boom_left);
	}
	((Sprite*)boom)->removeAllChildren();
	this->removeChild((Sprite*)boom);
}
void WhiteBlackScene::endgame(CCNode* pTarget, void* scene) {
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, MenuScene::createScene(), Color3B(0, 100, 100)));
}
void WhiteBlackScene::boom_boom(Sprite* boom) {
	auto scaleTo_s = ScaleTo::create(0.5, 0.5);
	auto scaleTo_b = ScaleTo::create(0.5, 1.0);
	auto mySequence = Sequence::create(scaleTo_s, scaleTo_b, scaleTo_s->clone(), scaleTo_b->clone(),
									   CCCallFuncND::create(this, callfuncND_selector(WhiteBlackScene::boom_finish), (void*)boom),
									   CCDelayTime::create(0.5), 
									   CCCallFuncND::create(this, callfuncND_selector(WhiteBlackScene::boom_end), (void*)boom),
									   nullptr);
	boom->runAction(mySequence);
}

void WhiteBlackScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event *event) {
	if (actor&&star) {
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
				float x = actor->getPosition().x;
				float y = actor->getPosition().y;
				auto boom_1 = Sprite::create();
				boom_1->initWithFile("w_heart.png");
				boom_1->setAnchorPoint(Vec2(0.5, 0.5));
				boom_1->setPosition(Vec2(x, y));
				boom_1->setTag(1);
				this->addChild(boom_1);
				boom_boom(boom_1);
			}
		}

		if (keycode == EventKeyboard::KeyCode::KEY_ENTER) {
			if (star->boom > 0) {
				star->boom--;
				float x = star->getPosition().x;
				float y = star->getPosition().y;
				auto boom_2 = Sprite::create();
				boom_2->initWithFile("b_heart.png");
				boom_2->setAnchorPoint(Vec2(0.5, 0.5));
				boom_2->setPosition(Vec2(x, y));
				boom_2->setTag(2);
				this->addChild(boom_2);
				boom_boom(boom_2);
			}
		}
	}
}

void WhiteBlackScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event *event) {
	if (actor&&star) {
		keys[keycode] = false;
		if ((keycode == EventKeyboard::KeyCode::KEY_UP_ARROW && actor->state == 3)
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
}

bool WhiteBlackScene::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (keys[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}

void WhiteBlackScene::update(float dt) {
	if (actor&&star) {
		if (isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW)) {
			float x = actor->getPosition().x;
			float y = actor->getPosition().y;
			if (y >= 0) {
				actor->setPosition(x, y - 2);
			}
		}
		else if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {
			float x = actor->getPosition().x;
			float y = actor->getPosition().y;
			if (x >= 20) {
				actor->setPosition(x - 2, y);
			}
		}
		else if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
			float x = actor->getPosition().x;
			float y = actor->getPosition().y;
			if (x <= 1024) {
				actor->setPosition(x + 2, y);
			}
		}
		else if (isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW)) {
			float x = actor->getPosition().x;
			float y = actor->getPosition().y;
			if (y <= 718) {
				actor->setPosition(x, y + 2);
			}
		}

		if (isKeyPressed(EventKeyboard::KeyCode::KEY_S)) {
			float xx = star->getPosition().x;
			float yy = star->getPosition().y;
			if (yy >= 0) {
				star->setPosition(xx, yy - 2);
			}
		}
		else if (isKeyPressed(EventKeyboard::KeyCode::KEY_A)) {
			float xx = star->getPosition().x;
			float yy = star->getPosition().y;
			if (xx >= 20) {
				star->setPosition(xx - 2, yy);
			}
		}
		else if (isKeyPressed(EventKeyboard::KeyCode::KEY_D)) {
			float xx = star->getPosition().x;
			float yy = star->getPosition().y;
			if (xx <= 1024) {
				star->setPosition(xx + 2, yy);
			}
		}
		else if (isKeyPressed(EventKeyboard::KeyCode::KEY_W)) {
			float xx = star->getPosition().x;
			float yy = star->getPosition().y;
			if (yy <= 718) {
				star->setPosition(xx, yy + 2);
			}
		}
	}
}
