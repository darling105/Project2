#include "PauseGame.h"
#include "Manager/GameManager.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"

USING_NS_CC;

bool PauseGame::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // Tạo một nền màu đen với độ trong suốt 50%
    ui::Button* _resumeButton = ui::Button::create("Buttons/Icon37.png");
    _resumeButton->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));
    _resumeButton->addClickEventListener(CC_CALLBACK_1(PauseGame::onResumeButtonClicked, this));
    this->addChild(_resumeButton);
    return true;
}

void PauseGame::show()
{
    this->setVisible(true);

    // Tạm dừng game
    GameManager::getInstance()->pauseGame();
}

void PauseGame::hide()
{
    this->setVisible(false);

    // Tiếp tục game
    GameManager::getInstance()->resumeGame();
}

void PauseGame::onResumeButtonClicked(cocos2d::Ref* sender)
{
    hide();
}