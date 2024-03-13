#include "GameScene.h"
#include "Scene/MainMenuScene.h"
#include "Maps/Map1.h"
#include "Maps/Map2.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Maps/Map3.h"


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
	

	auto button1 = ui::Button::create("Buttons/Button_Normal.png", "Buttons/Button_Press.png", "Buttons/Button_Disable.png");
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
			log("Map1 Cliked");
			break;
		
		}
		});

	this->addChild(button1);
	if (Character::isMap1Completed()) {
		auto button2 = ui::Button::create("Buttons/Button_Normal.png", "Buttons/Button_Press.png", "Buttons/Button_Disable.png");
		button2->setTitleText("Map 2");
		button2->setTitleColor(Color3B::BLACK);
		button2->setPosition(Vec2(visibleSize.width / 2 + 50, visibleSize.height / 2 - 100));
		button2->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type) {
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				auto map2Scene = Map2::create();
				Director::getInstance()->replaceScene(map2Scene);
				log("Map2 Clicked");
				break;
			}
			});
		this->addChild(button2);
	}

	if (Character::isMap1Completed()) {
		auto button3 = ui::Button::create("Buttons/Button_Normal.png", "Buttons/Button_Press.png", "Buttons/Button_Disable.png");
		button3->setTitleText("Map 3");
		button3->setTitleColor(Color3B::BLACK);
		button3->setPosition(Vec2(visibleSize.width / 2 + 200, visibleSize.height / 2 - 100));
		button3->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type) {
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				auto map3Scene = Map3::create();
				Director::getInstance()->replaceScene(map3Scene);
				log("Map3 Clicked");
				break;
			}
			});
		this->addChild(button3);
	}
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


