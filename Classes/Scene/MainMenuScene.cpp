#include "MainMenuScene.h"

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

    auto _background = Sprite::create("BackGround/Background.png");
    _background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    _background->setScale(2.25f);
    this->addChild(_background);

    Vector<MenuItem*> MenuItems;
    MenuItemFont::setFontSize(28);
    auto miFont = MenuItemFont::create("Play", [&](Ref* sender)
        {
            
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




