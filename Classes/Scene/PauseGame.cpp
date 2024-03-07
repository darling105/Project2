#include "PauseGame.h"
#include "Manager/GameManager.h"
#include "Scene/MainMenuScene.h"
#include "Scene/SettingScene.h"
#include "ButtonController/ButtonController.h"
#include "Camera/CameraFollow.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"

USING_NS_CC;

LayerColor* PauseGame::create()
{
    auto newObject = new PauseGame();
    if (newObject != nullptr && newObject->init())
    {
        newObject->autorelease();
        return newObject;
    }

    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool PauseGame::init()
{
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 0)))
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto pauseWindow = Sprite::create("BackGround/Menu.png");
    pauseWindow->setScale(2.0f);
    this->addChild(pauseWindow);
    auto windowSize = pauseWindow->getContentSize();

    auto resumeButton = MenuItemImage::create("Buttons/Icon37.png", "Buttons/Icon37.png", CC_CALLBACK_1(PauseGame::callResume, this));
    auto menuButton = MenuItemImage::create("Buttons/Icon02.png", "Buttons/Icon02.png", CC_CALLBACK_1(PauseGame::goToMainMenuScene, this));
    auto settingButton = MenuItemImage::create("Buttons/Icon05.png", "Buttons/Icon05.png", CC_CALLBACK_1(PauseGame::goToSettingScene, this));
     
    auto pauseMenuScene = Menu::create(settingButton, resumeButton, menuButton, nullptr);
    pauseMenuScene->setPosition(Vec2(windowSize.width / 2, windowSize.height / 8));
    pauseMenuScene->alignItemsHorizontallyWithPadding(30);
    pauseWindow->addChild(pauseMenuScene);
    this->scheduleUpdate();         
    return true;
}

void PauseGame::goToMainMenuScene(Ref* sender)
{
    Director::getInstance()->resume();
    this->removeFromParent();
    Director::getInstance()->replaceScene(MainMenu::create());
}

void PauseGame::callResume(Ref* sender)
{
    Director::getInstance()->resume();
    //ButtonController::getInstance()->showStopMenu(true);
    this->removeFromParent();
}

void PauseGame::goToSettingScene(Ref* sender)
{
    auto settingScene = SettingScene::create();
    addChild(settingScene, INT_MAX);
}

void PauseGame::onEnter()
{
    LayerColor::onEnter(); // Gọi phương thức onEnter của lớp cha

    // Lấy thông tin camera
    auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();

    // Lấy vị trí của camera
    auto cameraPosition = camera->getPosition();

    // Đặt vị trí mới cho PauseGame
    this->setPosition(cameraPosition);

    // Thêm PauseGame vào CameraFollow (nếu có)
    if (auto cameraFollow = dynamic_cast<CameraFollow*>(camera->getParent())) {
        cameraFollow->addChild(this);
    }
}
