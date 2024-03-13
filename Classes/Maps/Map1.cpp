#include "Maps/BaseMap.h"
#include "Map1.h"
#include "Scene/GameScene.h"
#include "MapUtilities/GameMap.h"
#include "StateMachine/StateMachine.h"
#include "Character/Character.h"
#include "ButtonController/ButtonController.h"
#include "Scene/GameOverScene.h"
#include "PhysicRender/PhysicGround.h"
#include "Camera/CameraFollow.h"
#include "PhysicRender/Stair.h"
#include "Coin/Coin.h"
#include "HealthController/HealthController.h"
#include "HealthController/HealthBarEmpty.h"
#include "Score/Score.h"


Map1* Map1::create() {
    auto newObject = new Map1();
    if (newObject != nullptr && newObject->init()) {
        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}



bool Map1::init() {
    if (!BaseMap::initWithPhysics()) {
        return false;
    }

    addBackground("BackGround/DeltaBG.jpg");
    addGameMap("Maps/map1.tmx");
    if (_gameMap == nullptr) {
        CCLOG("Error: _gameMap is nullptr after calling addGameMap!");
    }
    this->setTag(10);
    createMenu();
    createPhysicsWorld();
    addCharacter1();
    addMap1Enemies();
    createGroundPhysics();
    createButtonController();
    addLadder();
    addFinish();
    addSpike();
    addCoin();
    addObjects();
    createPolygonPhysics();
    createHealthBar();
    createCheckPoint();
    addScore();
    this->scheduleUpdate();
    return true;
}

void Map1::onEnter()
{
    Scene::onEnter();
    Score::getInstance()->reset();
    auto _char = _character->getCharacter(0);
    Size size = Director::getInstance()->getOpenGLView()->getFrameSize();
    auto mapSize = _gameMap->getContentSize();
    Rect boundingBox = { size.width / 2,size.height / 2,3680 - size.width / 2 - size.width / 2,1632 - size.height / 2 - size.height / 2 };
    auto buttonInstace = ButtonController::getInstance();

    auto _healthBar = HealthController::getInstance();
    
    auto _healthEmpty = HealthBarEmpty::getInstance( "/Character/Health/Healthbar_empty.png");
    auto _scoreLabel = Score::getInstance();
    CameraFollow* cam = CameraFollow::create(_char, boundingBox, buttonInstace, _healthBar, _healthEmpty, _scoreLabel);
    this->addChild(cam);
}
void Map1::callPauseScene(Ref* sender)
{
    auto pauseWindow = PauseGame::create();
    addChild(pauseWindow, INT_MAX);
    Director::getInstance()->pause();
}
void Map1::callGameOver(Ref* sender)
{
    auto gameOverScene = GameOverScene::create();
    addChild(gameOverScene, INT_MAX);

}

