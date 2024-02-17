#include "MainMenuScene.h"
#include "Scene/GameScene.h"
#include "Scene/SettingScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

bool MainMenu::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto _background = Sprite::create("BackGround/Background1.png");
    _background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    _background->setScale(2.25f);
    this->addChild(_background);
    auto buttonExit = ui::Button::create("Buttons/Icon42.png");
    buttonExit->setPosition(Vec2(visibleSize.width / 2-150, visibleSize.height / 2 ));
    buttonExit->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            Director::getInstance()->end();
            log("Exit");
            break;
        }
        });
    this->addChild(buttonExit);
    auto buttonPlay = ui::Button::create("Buttons/Icon37.png");
    buttonPlay->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    buttonPlay->setScale(2.0f);
    buttonPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
        {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                auto gameScene = GameScene::create();
                Director::getInstance()->replaceScene(gameScene);
                log("Play");
                break;
            }
        });
    this->addChild(buttonPlay);
    auto buttonSetting = ui::Button::create("Buttons/Icon05.png");
    buttonSetting->setPosition(Vec2(visibleSize.width / 2 + 150, visibleSize.height / 2));
    buttonSetting->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            auto settingScene = SettingScene::create();
            Director::getInstance()->replaceScene(settingScene);
            log("Exit");
            break;
        }
        });
    this->addChild(buttonSetting);
    
    

    return true;
}
void MainMenu::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void MainMenu::goToGameScene()
{
    auto gameScene = Scene::create();
    Director::getInstance()->pushScene(gameScene);
}
