#include "Map3.h"
#include "Scene/GameScene.h"
#include "ui/CocosGUI.h"
#include "Character/Character.h"
#include "ButtonController/ButtonController.h"
#include "HealthController/HealthBarEmpty.h"
#include "HealthController/HealthController.h"
#include "Score/Score.h"

USING_NS_CC;



Map3* Map3::create() {
    auto newObject = new Map3();
    if (newObject != nullptr && newObject->init()) {
        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}



bool Map3::init() {
    if (!BaseMap::initWithPhysics()) {
        return false;
    }

    addBackground("BackGround/CaveBG.jpg");
    addGameMap("Maps/map3.tmx");
    if (_gameMap == nullptr) {
        CCLOG("Error: _gameMap is nullptr after calling addGameMap!");
    }
    this->setTag(05);
    createMenu();
    createPhysicsWorld();
    addCharacter3();
    addMap3Enemies();
    createGroundPhysics();
    createButtonController();
    addLadder();
    addFinish();
    createPolygonPhysics();
    createHealthBar();
    addCoin();
    addScore();
    addObjects();
    addObjectsMap3();
    createCheckPoint();
    this->scheduleUpdate();
    return true;
}

void Map3::goToGameScene()
{
    if (ButtonController::getInstance()->getParent() != nullptr) {
        ButtonController::getInstance()->removeFromParent();
    }

    Director::getInstance()->popScene();
}

void Map3::onEnter()
{
    Scene::onEnter();
    Score::getInstance()->reset();
    auto _char = _character->getCharacter(0);
    Size size = Director::getInstance()->getOpenGLView()->getFrameSize();
    auto mapSize = _gameMap->getContentSize();
    Rect boundingBox = { size.width / 2,size.height / 2,3680 - size.width / 2 - size.width / 2,1632 - size.height / 2 - size.height / 2 };
    auto buttonInstace = ButtonController::getInstance();

    auto _healthBar = HealthController::getInstance();

    auto _healthEmpty = HealthBarEmpty::getInstance("/Character/Health/Healthbar_empty.png");
    auto _scoreLabel = Score::getInstance();
    CameraFollow* cam = CameraFollow::create(_char, boundingBox, buttonInstace, _healthBar, _healthEmpty, _scoreLabel);
    this->addChild(cam);
}
void Map3::callPauseScene(Ref* sender)
{
    auto pauseWindow = PauseGame::create();
    addChild(pauseWindow, INT_MAX);
    Director::getInstance()->pause();
}



