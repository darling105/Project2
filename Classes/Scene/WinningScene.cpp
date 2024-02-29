#include "WinningScene.h"
#include "Scene/MainMenuScene.h"
#include "Maps/Map2.h"

Scene* WinningScene::create()
{
	auto newObject = new WinningScene();
	if (newObject != nullptr && newObject->init())
	{
		newObject->autorelease();
		return newObject;
	}
	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool WinningScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_background = Sprite::create("Background/Background1.png");
	_background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	_background->setScale(2.25f);
	this->addChild(_background);
	auto windowSize = _background->getContentSize();
	auto menuButton = MenuItemImage::create("Buttons/Icon02.png", "Buttons/Icon02.png", CC_CALLBACK_1(WinningScene::goToMainMenuScene, this));
	auto winningScene = Menu::create(menuButton, nullptr);
	winningScene->setPosition(Vec2(windowSize.width / 2, windowSize.height / 8));
	winningScene->alignItemsHorizontallyWithPadding(30);
	_background->addChild(winningScene);
	this->scheduleUpdate();
	return true;
}

void WinningScene::goToMainMenuScene(Ref* sender)
{
	Director::getInstance()->resume();
	this->removeFromParent();
	Director::getInstance()->replaceScene(Map2::create());
}
