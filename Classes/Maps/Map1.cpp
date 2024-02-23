#include "Maps/BaseMap.h"
#include "Map1.h"
#include "Scene/GameScene.h"
#include "MapUtilities/GameMap.h"
#include "StateMachine/StateMachine.h"
#include "Character/Character.h"
#include "ButtonController/ButtonController.h"
#include "PhysicRender/PhysicGround.h"
#include "Camera/CameraFollow.h"
#include "Enemy/Enemy.h"
#include "PhysicRender/Stair.h"

ButtonController* _buttonController;

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
    addBackground("BackGround/Background2.png");
    addGameMap("Maps/map1.tmx");
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
    this->scheduleUpdate();
    return true;
}

void Map1::goToGameScene()
{
    if (ButtonController::getInstance()->getParent() != nullptr){
        ButtonController::getInstance()->removeFromParent();
    }
        
	Director::getInstance()->popScene();
}

void Map1::onEnter()
{
    Scene::onEnter();
    auto _char = _character->getCharacter(0);
    Size size = Director::getInstance()->getOpenGLView()->getFrameSize();
    auto mapSize = _gameMap->getContentSize();
    Rect boundingBox = { size.width / 2,size.height / 2,3680 - size.width / 2 - size.width / 2,1632 - size.height / 2 - size.height / 2 };
    auto buttonInstace = ButtonController::getInstance();
    CameraFollow* cam = CameraFollow::create(_char, boundingBox, buttonInstace);
    this->addChild(cam);

   
}

