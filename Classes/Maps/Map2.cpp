#include "Map2.h"
#include "Scene/GameScene.h"
#include "ui/CocosGUI.h"
#include "Character/Character.h"
#include "ButtonController/ButtonController.h"
#include "HealthController/HealthBarEmpty.h"
#include "HealthController/HealthController.h"
#include "Score/Score.h"
#include "Time/Time.h"

USING_NS_CC;    


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

    addBackground("BackGround/CaveBG.jpg");
    addGameMap("Maps/map2.tmx");
    if (_gameMap == nullptr) {
        CCLOG("Error: _gameMap is nullptr after calling addGameMap!");
    }
    this->setTag(05);
    createMenu();
    createPhysicsWorld();
    addCharacter2();
    addMap2Enemies();
    createGroundPhysics();
    createButtonController();
    addLadder();
    addFinish();
    createPolygonPhysics();
    createHealthBar();
    addCoin();
    addScore();
    addObjects();
    createCheckPoint();
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
    Score::getInstance()->reset();
    auto _char = _character->getCharacter(0);
    Size size = Director::getInstance()->getOpenGLView()->getFrameSize();
    auto mapSize = _gameMap->getContentSize();
    Rect boundingBox = { size.width / 2,size.height / 2,3680 - size.width / 2 - size.width / 2,1632 - size.height / 2 - size.height / 2 };
    auto buttonInstace = ButtonController::getInstance();

    auto _healthBar = HealthController::getInstance();

    auto _healthEmpty = HealthBarEmpty::getInstance("/Character/Health/Healthbar_empty.png");
    auto _scoreLabel = Score::getInstance();
    auto _timeLabel = Time::getInstance();
    CameraFollow* cam = CameraFollow::create(_char, boundingBox, buttonInstace, _healthBar, _healthEmpty, _scoreLabel, _timeLabel);
    this->addChild(cam);
}
void Map2::callPauseScene(Ref* sender)
{
    auto pauseWindow = PauseGame::create();
    addChild(pauseWindow, INT_MAX);
    Director::getInstance()->pause();
}



