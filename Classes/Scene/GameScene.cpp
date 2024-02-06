#include "GameScene.h"
#include "Scene/MainMenuScene.h"

USING_NS_CC;

Scene* GameScene::create()
{
	auto newObject = new GameScene();
	if (newObject != nullptr && newObject->init())
	{
		newObject->autorelease();
		return newObject;
	}

	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool GameScene::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vector<MenuItem*> MenuItems;
	auto miFont = MenuItemFont::create("Back", [&](Ref* sender) {
		auto mainMenuScene = MainMenu::create();
		Director::getInstance()->replaceScene(mainMenuScene);
		log("Main Menu Clicked");
		});
	miFont->setPosition(Vec2(visibleSize.width / 2 - 1100, visibleSize.height / 2 - 50));
	MenuItems.pushBack(miFont);
	auto menuA = Menu::createWithArray(MenuItems);
	this->addChild(menuA, 1);

	return true;
}

void GameScene::goToMainMenuScene()
{
	Director::getInstance()->popScene();
}


