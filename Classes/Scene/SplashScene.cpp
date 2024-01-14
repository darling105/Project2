#include "SplashScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

void SplashScene::goToMainMenuScene()
{
	this->scheduleOnce([](float dt)
		{
			Director::getInstance()->
			replaceScene(TransitionFade::create(1.0, MainMenu::create()));
		},1.5, "switch_to_scene2");
}

Scene* SplashScene::createScene()
{
	return SplashScene::create();
}

bool SplashScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto _background = Sprite::create("BackGround/Logosplash.png");
	_background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	_background->setOpacity(100);
	this->addChild(_background);
	goToMainMenuScene();

	return true;
}





