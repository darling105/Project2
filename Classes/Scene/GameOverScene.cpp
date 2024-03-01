#include "GameOverScene.h"
#include "Scene/MainMenuScene.h"
#include "Camera/CameraFollow.h"
#include "Maps/Map1.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"

LayerColor* GameOverScene::create()
{
	auto newObject = new GameOverScene();
	if (newObject != nullptr && newObject->init())
	{
		newObject->autorelease();
		return newObject;
	}
	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool GameOverScene::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 0)))
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto gameOverWindow = Sprite::create("Background/GameOver.png");
	gameOverWindow->setScale(2.0f);
	this->addChild(gameOverWindow);
	auto windowSize = gameOverWindow->getContentSize();

	auto menuButton = MenuItemImage::create("Buttons/Icon02.png", "Buttons/Icon02.png", CC_CALLBACK_1(GameOverScene::goToMainMenuScene, this));
	auto gameOverScene = Menu::create(menuButton, nullptr);
	gameOverScene->setPosition(Vec2(windowSize.width / 2, windowSize.height / 8));
	gameOverScene->alignItemsHorizontallyWithPadding(30);
	gameOverWindow->addChild(gameOverScene);
	this->scheduleUpdate();
	return true;
}

void GameOverScene::goToMainMenuScene(Ref* sender)
{
	Director::getInstance()->getRunningScene()->removeAllChildrenWithCleanup(true);
	auto scene = Map1::create();
	Director::getInstance()->replaceScene(scene);
}

void GameOverScene::onEnter()
{
	LayerColor::onEnter();

	auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();

	auto cameraPosition = camera->getPosition();

	this->setPosition(cameraPosition);

	if (auto cameraFollow = dynamic_cast<CameraFollow*>(camera->getParent())) {
		cameraFollow->addChild(this);
	}
}

void GameOverScene::update()
{

}
