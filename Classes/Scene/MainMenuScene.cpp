#include "MainMenuScene.h"
#include "Scene/GameScene.h"

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

    Vector<MenuItem*> MenuItems;
    auto lblMenuExit = Label::createWithTTF("Exit", "fonts/arial.ttf", 28);
    auto miExit = MenuItemLabel::create(lblMenuExit, CC_CALLBACK_1(MainMenu::menuCloseCallback, this));
    miExit->setPosition(Vec2(0, -50));
    MenuItems.pushBack(miExit);
    MenuItemFont::setFontSize(28);
    auto miFont = MenuItemFont::create("Play", [&](Ref* sender)
        {
            auto gameScene = GameScene::create();
            Director::getInstance()->replaceScene(gameScene);
            log("Game Scene Cliked");
        });
    miFont->setPosition(Vec2(0, 0));
    MenuItems.pushBack(miFont);
    auto miFont2 = MenuItemFont::create("Setting", [&](Ref* sender)
        {

        });
    miFont->setPosition(Vec2(0, 50));
    MenuItems.pushBack(miFont2);
    auto menuA = Menu::createWithArray(MenuItems);
    this->addChild(menuA);

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
