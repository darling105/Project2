#include "Map1.h"
#include "Scene/GameScene.h"
#include "MapUtilities/GameMap.h"

Scene* Map1::create()
{
	auto newObject = new Map1();
	if (newObject != nullptr && newObject->init())
	{
		newObject->autorelease();
		return newObject;
	}
	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool Map1::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vector<MenuItem*> MenuItems;
	auto miFont = MenuItemFont::create("Back", [&](Ref* sender) {
		auto gameScene = GameScene::create();
		Director::getInstance()->replaceScene(gameScene);
		log("Game Scene Clicked");
		});
	miFont->setPosition(Vec2(visibleSize.width / 2 - 1100, visibleSize.height / 2 - 50));
	MenuItems.pushBack(miFont);
	auto menuA = Menu::createWithArray(MenuItems);
	this->addChild(menuA, 1);
	auto _background = Sprite::create("BackGround/Background2.png");
	_background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	_background->setScale(2.25f);
	this->addChild(_background);
	auto map1 = GameMap::create("Map/map1.tmx");
	this->addChild(map1);
	return true;
}

void Map1::goToGameScene()
{
	Director::getInstance()->popScene();
}
