#include "Map2.h"
#include "Scene/GameScene.h"
#include "ui/CocosGUI.h"
#include "Character/Character.h"
#include "ButtonController/ButtonController.h"

USING_NS_CC;    

ButtonController* _buttonController1;

Map2* Map2::create() {
    auto newObject = new Map2();
    if (newObject != nullptr && newObject->init()) {
        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}



bool Map2::init() {
    if (!BaseMap::initWithPhysics()) {
        return false;
    }

    addBackground("BackGround/Background2.png");
    addGameMap("Maps/map2.tmx");
    if (_gameMap == nullptr) {
        CCLOG("Error: _gameMap is nullptr after calling addGameMap!");
    }
    createMenu();
    createPhysicsWorld();
    addCharacter();
    addEnemies();
    createGroundPhysics();
    createButtonController();
    addLadder();
    addFinish();
    createPolygonPhysics();
    this->scheduleUpdate();
    return true;
}

void Map2::goToGameScene()
{
    if (ButtonController::getInstance()->getParent() != nullptr) {
        ButtonController::getInstance()->removeFromParent();
    }

    Director::getInstance()->popScene();
}

void Map2::onEnter()
{
    Scene::onEnter();
    auto _char1 = _character->getCharacter(0);
    Size size1 = Director::getInstance()->getOpenGLView()->getFrameSize();
    auto mapSize1 = _gameMap->getContentSize();
    Rect boundingBox1 = { size1.width / 2,size1.height / 2,3680 - size1.width / 2 - size1.width / 2,1632 - size1.height / 2 - size1.height / 2 };
    auto buttonInstace1 = ButtonController::getInstance();
    CameraFollow* cam1 = CameraFollow::create(_char1, boundingBox1, buttonInstace1);
    this->addChild(cam1);
}
void Map2::callPauseScene(Ref* sender)
{
    auto pauseWindow = PauseGame::create();
    addChild(pauseWindow, INT_MAX);
    Director::getInstance()->pause();
}



