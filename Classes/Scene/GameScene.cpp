#include "GameScene.h"
#include "Scene/MainMenuScene.h"
#include "Maps/Map1.h"
#include "Maps/Map2.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"


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
	

	auto button1 = ui::Button::create("Button_Normal.png", "Button_Press.png", "Button_Disable.png");
	button1->setTitleText("Map 1");
	button1->setTitleColor(Color3B::BLACK);
	button1->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 - 100));
	button1->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			auto map1Scene = Map1::create();
			Director::getInstance()->replaceScene(map1Scene);
			log("Map2 Cliked");
			break;
		
		}
		});

	this->addChild(button1);
	auto button2 = ui::Button::create("Button_Normal.png", "Button_Press.png", "Button_Disable.png");
	button2->setTitleText("Map 2");
	button2->setTitleColor(Color3B::BLACK);
	button2->setPosition(Vec2(visibleSize.width / 2 + 50, visibleSize.height / 2 - 100));
	button2->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			auto map2Scene = Map2::create();
			Director::getInstance()->replaceScene(map2Scene);
			log("Map1 Cliked");
			break;

		}
		});

	this->addChild(button2);
	return true;
}

void GameScene::goToMainMenuScene()
{
	Director::getInstance()->popScene();
}

void GameScene::goToMap1()
{
	auto map1Scene = Scene::create();
	Director::getInstance()->pushScene(map1Scene);
}


