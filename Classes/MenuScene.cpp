#include "MenuScene.h"
#include "FirstScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
Scene* MenuScene::createScene()
{
    return MenuScene::create();
}
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}
bool MenuScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto colorLayer = CCLayerColor::create();
	colorLayer->initWithColor(ccc4(0, 100, 200, 255));
	this->addChild(colorLayer, -1);

    auto closeItem = MenuItemImage::create("CloseNormal.png","CloseSelected.png",
                                           CC_CALLBACK_1(MenuScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }
	auto startItem=MenuItemImage::create("Play.png","PlayPress.png",
											CC_CALLBACK_1(MenuScene::gameStartCallback, this));
	if (startItem == nullptr||
		startItem->getContentSize().width <= 0 || startItem->getContentSize().height <= 0)
	{
		problemLoading("'Play.png' and 'PlayPress.png'");
	}
	else
	{
		startItem->setAnchorPoint(Vec2(0.5, 0.5));
		startItem->setScale(0.4);
		float x = origin.x + visibleSize.width / 2;
		float y = origin.y + visibleSize.height * 0.5 / 4;
		startItem->setPosition(Vec2(x, y));
	}
    auto menu = Menu::create(closeItem, startItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    auto label = Label::createWithTTF("My Game", "fonts/Marker Felt.ttf", 28);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y + visibleSize.height - label->getContentSize().height));
        this->addChild(label, 1);
    }
	auto sprite = Sprite::create("MyGame.png");
	if (sprite == nullptr) {
		problemLoading("MyGame.png");
	}
	else {
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		sprite->setScale(0.4);
		this->addChild(sprite, 0);
	}
    return true;
}
void MenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
void MenuScene::gameStartCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, FirstScene::create(), Color3B(0, 100, 100)));
}
