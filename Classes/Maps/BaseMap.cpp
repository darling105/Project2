#include "BaseMap.h"
#include "ButtonController/ButtonController.h"
#include "Character/Character.h"
#include "MapUtilities/GameMap.h"
#include "PhysicRender/PhysicGround.h"
#include "PhysicRender/Stair.h"
#include "PhysicRender/Finish.h"
#include "PhysicRender/PolygonGround.h"
#include "PhysicRender/Spike.h"
#include "Scene/GameScene.h"
#include "Scene/PauseGame.h"
#include "Scene/GameOverScene.h"
#include "Enemy/Bat/Bat.h"
#include "Enemy/Robot/Enemy.h"
#include "Enemy/Creep/Creep.h"
#include "Objects/Trampoline/Trampoline.h"
#include "Coin/Coin.h"
#include "Enemy/Pupple/Pupple.h"
#include "Enemy/Void/Void.h"
#include "HealthController/HealthController.h"
#include "HealthController/HealthBarEmpty.h"
#include "Enemy/William/William.h"
#include "PhysicRender/CheckPoint.h"
#include "Score/Score.h"
#include "Enemy/Ghost/Ghost.h"
#include "Objects/Saw/Saw.h"
#include "Enemy/Tiny/Tiny.h"
#include "Objects/Platform/Platform.h"
#include "Time/Time.h"

USING_NS_CC;

bool BaseMap::init() {
    if (!Scene::init()) {
        return false;
    }
    createPhysicsWorld();
    createMenu();
    createButtonController();
    createGroundPhysics();
    return true;
}

void BaseMap::createPhysicsWorld() {
    auto _physicsWorld = this->getPhysicsWorld();
    _physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    _physicsWorld->setGravity(Vec2(0, -60));
    _physicsWorld->setFixedUpdateRate(600.0f);
    _physicsWorld->setSpeed(5.0);
}

void BaseMap::createMenu() {
    
}

void BaseMap::createButtonController() {

    auto _buttonController1 = ButtonController::getInstance();
    this->addChild(_buttonController1, 2);
}

void BaseMap::createGroundPhysics() {
    auto objectPhysic = _gameMap->getObjectGroup("PhysicsObject");
    auto groundPhysics = PhysicGround::create(objectPhysic);
    this->addChild(groundPhysics, 1);
}

void BaseMap::createPolygonPhysics()
{
    auto objectPolygon = _gameMap->getObjectGroup("PolygonPhysicsObject");
    auto polygonPhysics = PolygonGround::create(objectPolygon);
    this->addChild(polygonPhysics);
}

void BaseMap::createHealthBar()
{
    auto _healthEmpty = HealthBarEmpty::getInstance("Character/Health/Healthbar_empty.png");
    _healthEmpty->setScale(2.0f);
    this->addChild(_healthEmpty, 2);

    auto _healthBar = HealthController::getInstance();
    //_healthBar->setCurrentHealth(6);
    _healthBar->setMaxHealth(3);
    this->addChild(_healthBar, 3);
}

void BaseMap::createCheckPoint()
{
    auto objectCheckPoint = _gameMap->getObjectGroup("CheckPoint");
    auto checkPointPhysics = CheckPoint::create(objectCheckPoint);
    this->addChild(checkPointPhysics);

}

void BaseMap::addCharacter1() {

    EntityInfo* _characterInfo = new EntityInfo("character");
    auto _characterInstance = Character::getInstance(_characterInfo);
    _characterInstance->resetInstance();
    _characterInstance->addCharacter(_characterInfo);
    auto _character = _characterInstance->getCharacter(0);
    _character->getMap("Map_1");
    TMXObjectGroup* objectGroup = _gameMap->getObjectGroup("CharacterSpawnPoint");
    ValueMap charSpawnPoint = objectGroup->getObject("SpawnPoint");
    Vec2 _position;
    _position.x = charSpawnPoint["x"].asFloat();
    _position.y = charSpawnPoint["y"].asFloat();
    _character->setPosition(_position);
    this->addChild(_character, 0);
}

void BaseMap::addCharacter2() {
    EntityInfo* _characterInfo = new EntityInfo("dude");
    auto _characterInstance = Character::getInstance(_characterInfo);
    _characterInstance->resetInstance();
    _characterInstance->addCharacter(_characterInfo);
    auto _character1 = _characterInstance->getCharacter(0);
    _character1->getMap("Map_2");
    TMXObjectGroup* objectGroup = _gameMap->getObjectGroup("CharacterSpawnPoint");
    ValueMap charSpawnPoint = objectGroup->getObject("SpawnPoint");
    Vec2 _position;
    _position.x = charSpawnPoint["x"].asFloat();
    _position.y = charSpawnPoint["y"].asFloat();
    _character1->setPosition(_position);
    this->addChild(_character1, 0);
}

void BaseMap::addCharacter3()
{
    EntityInfo* _characterInfo = new EntityInfo("owlet");
    auto _characterInstance = Character::getInstance(_characterInfo);
    _characterInstance->resetInstance();
    _characterInstance->addCharacter(_characterInfo);
    auto _character1 = _characterInstance->getCharacter(0);
    _character1->getMap("Map_3");
    TMXObjectGroup* objectGroup = _gameMap->getObjectGroup("CharacterSpawnPoint");
    ValueMap charSpawnPoint = objectGroup->getObject("SpawnPoint");
    Vec2 _position;
    _position.x = charSpawnPoint["x"].asFloat();
    _position.y = charSpawnPoint["y"].asFloat();
    _character1->setPosition(_position);
    this->addChild(_character1, 1);
}

void BaseMap::addBackground(const std::string& backgroundImagePath) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto _background = Sprite::create(backgroundImagePath);
    _background->setPosition(visibleSize / 2);
    _background->setScale(2.25f);
    this->addChild(_background);
}

void BaseMap::addMap1Enemies() {
    int numEnemies = 3;
    int index = 0;

    TMXObjectGroup* puppleObjectGroup = _gameMap->getObjectGroup("PuppleSpawnPoint");
    auto puppleObjects = puppleObjectGroup->getObjects();
    int puppleIndex = 0;
    for (const auto& object : puppleObjects) {
        ValueMap puppleSpawnPoint = object.asValueMap();
        Vec2 _position;
        _position.x = puppleSpawnPoint["x"].asFloat();
        _position.y = puppleSpawnPoint["y"].asFloat();
        auto pupple = Pupple::create(new EntityInfo("pupple"));
        pupple->setPosition(_position);
        if (puppleIndex <= 3) {
            pupple->setupPupple(200, Vec2(-1, 0));
        }
        else {
            pupple->setupPupple(200, Vec2(1, 0));
        }
        this->addChild(pupple, 2);
        puppleIndex++;
    }

    TMXObjectGroup* voidObjectGroup = _gameMap->getObjectGroup("VoidSpawnPoint");
    auto voidObjects = voidObjectGroup->getObjects();
    for (const auto& object : voidObjects) {
        ValueMap voidSpawnPoint = object.asValueMap();
        Vec2 _position;
        _position.x = voidSpawnPoint["x"].asFloat();
        _position.y = voidSpawnPoint["y"].asFloat();
        auto _void = Void::create(new EntityInfo("void"));
        _void->setPosition(_position);
        _void->setupVoid(-90, 2, Vec2(0, -1));
        this->addChild(_void, 2);
    }

    TMXObjectGroup* objectGroup = _gameMap->getObjectGroup("BatSpawnPoint");
    auto objects = objectGroup->getObjects();
    int batIndex = 0;
    for (const auto& object : objects) {
        ValueMap batSpawnPoint = object.asValueMap();
        Vec2 _position;
        _position.x = batSpawnPoint["x"].asFloat();
        _position.y = batSpawnPoint["y"].asFloat();
        bat = Bat::create(new EntityInfo("bat"));
        bat->setPosition(_position);
        if (batIndex == 0) {
            bat->setupBat(120, Vec2(1, 0));
        }
        else if (batIndex == 1) {
            bat->setupBat(200, Vec2(-1, 0));
        }
        else if (batIndex == 2) {
            bat->setupBat(80, Vec2(1, 0));
        }
        else {
            bat->setupBat(80, Vec2(-1, 0));
        }
        this->addChild(bat, 2);
        batIndex++;
    }

    TMXObjectGroup* williamObjectGroup = _gameMap->getObjectGroup("WilliamSpawnPoint");
    auto williamObjects = williamObjectGroup->getObjects();
    for (const auto& object : williamObjects) {
        ValueMap lineInfo = object.asValueMap();
        Vec2 _position;
        _position.x = lineInfo["x"].asFloat();
        _position.y = lineInfo["y"].asFloat();
        auto william = William::create(new EntityInfo("william"));
        william->setPosition(_position);
        this->addChild(william, 2);


    }
}

void BaseMap::addMap2Enemies()
{
    int index = 0;
    TMXObjectGroup* voidObjectGroup = _gameMap->getObjectGroup("VoidEnemySpawnPoint");
    auto voidObjects = voidObjectGroup->getObjects();
    for (const auto& object : voidObjects) {
        ValueMap voidSpawnPoint = object.asValueMap();
        Vec2 _position;
        _position.x = voidSpawnPoint["x"].asFloat();
        _position.y = voidSpawnPoint["y"].asFloat();
        auto _void = Void::create(new EntityInfo("void"));
        _void->setPosition(_position);
        if (index == 0) {
            _void->setupVoid(0, 2, Vec2(-1, 0));
        }
        else {
            _void->setupVoid(180, 2, Vec2(1, 0));
        }
        this->addChild(_void, 2);
        index++;
    }

    TMXObjectGroup* puppleObjectGroup = _gameMap->getObjectGroup("PuppleSpawnPoint");
    auto puppleObjects = puppleObjectGroup->getObjects();
    int puppleIndex = 0;
    for (const auto& object : puppleObjects) {
        ValueMap puppleSpawnPoint = object.asValueMap();
        Vec2 _position;
        _position.x = puppleSpawnPoint["x"].asFloat();
        _position.y = puppleSpawnPoint["y"].asFloat();
        auto pupple = Pupple::create(new EntityInfo("pupple"));
        pupple->setPosition(_position);
        if (puppleIndex <= 3) {
            pupple->setupPupple(200, Vec2(-1, 0));
        }
        else {
            pupple->setupPupple(200, Vec2(1, 0));
        }
        this->addChild(pupple, 2);
        puppleIndex++;
    }

    TMXObjectGroup* creepObjectGroup = _gameMap->getObjectGroup("CreepSpawnPoint");
    auto creepObjects = creepObjectGroup->getObjects();
    //int puppleIndex = 0;
    for (const auto& object : creepObjects) {
        ValueMap creepSpawnPoint = object.asValueMap();
        Vec2 _position;
        _position.x = creepSpawnPoint["x"].asFloat();
        _position.y = creepSpawnPoint["y"].asFloat();
        auto creep = Creep::create(new EntityInfo("creep"));
        creep->setPosition(_position);
        this->addChild(creep, 2);
        puppleIndex++;
    }

    TMXObjectGroup* ghostObjectGroup = _gameMap->getObjectGroup("GhostSpawnPoint");
    auto ghostObjects = ghostObjectGroup->getObjects();
    for (const auto& object : ghostObjects) {
        ValueMap ghostSpawnPoint = object.asValueMap();
        Vec2 _position;
        _position.x = ghostSpawnPoint["x"].asFloat();
        _position.y = ghostSpawnPoint["y"].asFloat();
        auto ghost = Ghost::create(new EntityInfo("ghost"));
        ghost->setPosition(_position);
        ghost->setSpeed(20);
        ghost->movingRightFirst();
        this->addChild(ghost, 2);
    }

    TMXObjectGroup* objectGroup = _gameMap->getObjectGroup("BatSpawnPoint");
    auto objects = objectGroup->getObjects();
    int batIndex = 0;
    for (const auto& object : objects) {
        ValueMap batSpawnPoint = object.asValueMap();
        Vec2 _position;
        _position.x = batSpawnPoint["x"].asFloat();
        _position.y = batSpawnPoint["y"].asFloat();
        bat = Bat::create(new EntityInfo("bat"));
        bat->setPosition(_position);
        if (batIndex == 0) {
            bat->setupBat(120, Vec2(1, 0));
        }
        else if (batIndex == 1) {
            bat->setupBat(200, Vec2(-1, 0));
        }
        else if (batIndex == 2) {
            bat->setupBat(80, Vec2(1, 0));
        }
        else {
            bat->setupBat(80, Vec2(-1, 0));
        }
        this->addChild(bat, 2);
        batIndex++;
    }
}

void BaseMap::addMap3Enemies()
{
    TMXObjectGroup* tinyObjectGroup = _gameMap->getObjectGroup("TinySpawnPoint");
    auto tinyObjects = tinyObjectGroup->getObjects();
    for (const auto& object : tinyObjects) {
        ValueMap tinySpawnPoint = object.asValueMap();
        Vec2 _position;
        _position.x = tinySpawnPoint["x"].asFloat();
        _position.y = tinySpawnPoint["y"].asFloat();
        auto tiny = Tiny::create(new EntityInfo("tiny"));
        tiny->setPosition(_position);
        tiny->setSpeed(30);
        this->addChild(tiny, 2);
    }

    TMXObjectGroup* ghostObjectGroup = _gameMap->getObjectGroup("GhostSpawnPoint");
    auto ghostObjects = ghostObjectGroup->getObjects();
    for (const auto& object : ghostObjects) {
        ValueMap ghostSpawnPoint = object.asValueMap();
        Vec2 _position;
        _position.x = ghostSpawnPoint["x"].asFloat();
        _position.y = ghostSpawnPoint["y"].asFloat();
        auto ghost = Ghost::create(new EntityInfo("ghost"));
        ghost->setPosition(_position);
        ghost->setSpeed(20);
        ghost->movingRightFirst();
        this->addChild(ghost, 2);
    }

    TMXObjectGroup* puppleObjectGroup = _gameMap->getObjectGroup("PuppleSpawnPoint");
    auto puppleObjects = puppleObjectGroup->getObjects();
    int puppleIndex = 0;
    for (const auto& object : puppleObjects) {
        ValueMap puppleSpawnPoint = object.asValueMap();
        Vec2 _position;
        _position.x = puppleSpawnPoint["x"].asFloat();
        _position.y = puppleSpawnPoint["y"].asFloat();
        auto pupple = Pupple::create(new EntityInfo("pupple"));
        pupple->setPosition(_position);
        if (puppleIndex == 2) {
            pupple->setupPupple(100, Vec2(-1, 0));
        }
        else {
            pupple->setupPupple(200, Vec2(1, 0));
        }
        this->addChild(pupple, 2);
        puppleIndex++;
    }
    int VoidIndex = 0;
    TMXObjectGroup* voidObjectGroup = _gameMap->getObjectGroup("VoidSpawnPoint");
    auto voidObjects = voidObjectGroup->getObjects();
    for (const auto& object : voidObjects) {
        ValueMap voidSpawnPoint = object.asValueMap();
        Vec2 _position;
        _position.x = voidSpawnPoint["x"].asFloat();
        _position.y = voidSpawnPoint["y"].asFloat();
        auto _void = Void::create(new EntityInfo("void"));
        _void->setPosition(_position);
        if (VoidIndex == 0) {
        _void->setupVoid(180, 2, Vec2(1, 0));
        }
        else {
            _void->setupVoid(-90, 2, Vec2(0, -1));
        }
        this->addChild(_void, 2);
        VoidIndex++;
    }
}

void BaseMap::addGameMap(const std::string& gameMapPath)
{
    _gameMap = GameMap::create(gameMapPath);
    this->addChild(_gameMap, 1);
}

void BaseMap::addLadder()
{
    auto objectLadder = _gameMap->getObjectGroup("Ladder");
    auto ladderPhysics = Stair::create(objectLadder);
    this->addChild(ladderPhysics);
}

void BaseMap::addFinish()
{
    auto objectFinish = _gameMap->getObjectGroup("Finish");
    auto finishPhysics = Finish::create(objectFinish);
    this->addChild(finishPhysics);
}

void BaseMap::addSpike()
{
    auto objectSpike = _gameMap->getObjectGroup("Spike");
    auto spikePhysics = Spike::create(objectSpike);
    this->addChild(spikePhysics);
}
void BaseMap::addCoin()
{
    int numTinySpawnCoin = 1;
    int coinIndex = 0;
    for (int i = 0; i < 7; i++) {
        TMXObjectGroup* objectGroup = _gameMap->getObjectGroup("CoinSpawnPoint");
        auto objectLargeCoins = objectGroup->getObjects();
        for (const auto& objectLargeCoin : objectLargeCoins) {
            ValueMap lineInfo = objectLargeCoin.asValueMap();
            Vec2 _position;
            _position.x = lineInfo["x"].asFloat();
            _position.y = lineInfo["y"].asFloat();
            auto coin = Coin::create(new EntityInfo("coin"));
            coin->setPosition(_position.x + 36 * (i + 1), _position.y + 16);
            this->addChild(coin, 2);
        }       
    }

    for (int i = 0; i < 2; i++) {
    TMXObjectGroup* smallCoinObjectGroup = _gameMap->getObjectGroup("SmallCoinSpawnPoint");
    auto objects = smallCoinObjectGroup->getObjects();
    for (const auto& object : objects) {
        ValueMap lineInfo = object.asValueMap();
        Vec2 _position;
        _position.x = lineInfo["x"].asFloat();
        _position.y = lineInfo["y"].asFloat();
        auto coin = Coin::create(new EntityInfo("coin"));
        coin->setPosition(_position.x + 16  + (i * 32), _position.y + 16);
        this->addChild(coin, 2);
    }
    }

    TMXObjectGroup* tinyCoinObjectGroup = _gameMap->getObjectGroup("TinyCoinSpawnPoint");
    auto objects = tinyCoinObjectGroup->getObjects();
    for (const auto& object : objects) {
        ValueMap lineInfo = object.asValueMap();
        Vec2 _position;
        _position.x = lineInfo["x"].asFloat();
        _position.y = lineInfo["y"].asFloat();
        auto coin = Coin::create(new EntityInfo("coin"));
        coin->setPosition(_position.x + 16, _position.y + 16);
        this->addChild(coin, 2);
        }
}
void BaseMap::addObjects()
{
    TMXObjectGroup* objectGroup = _gameMap->getObjectGroup("Trampoline");
    auto objects = objectGroup->getObjects();
    for (const auto& object : objects) {
        ValueMap trampolineSpawnPoint = object.asValueMap();
        Vec2 _position;
        _position.x = trampolineSpawnPoint["x"].asFloat();
        _position.y = trampolineSpawnPoint["y"].asFloat();
        auto trampoline = Trampoline::create(new EntityInfo("trampoline"));
        trampoline->setPosition(_position);
        this->addChild(trampoline, 2);
    }
}

void BaseMap::addObjectsMap3()
{
    int index = 0;
    TMXObjectGroup* sawGroup = _gameMap->getObjectGroup("Saw");
    auto sawObjects = sawGroup->getObjects();
    for (const auto& object : sawObjects) {
        ValueMap sawSpawnPoint = object.asValueMap();
        Vec2 _position;
        _position.x = sawSpawnPoint["x"].asFloat();
        _position.y = sawSpawnPoint["y"].asFloat();
        auto saw = Saw::create(new EntityInfo("saw"));
        if (index == 0) {
            saw->setSpeed(35.0f);
            saw->movingRightFirst();
        }
        else if (index == 1) {
            saw->setSpeed(10.0f);
            saw->movingLeftFirst();
        }
        else if (index == 2) {
            saw->setSpeed(20.0f);
            saw->movingRightFirst();
        }
        else if (index == 3) {
            saw->setSpeed(20.0f);
            saw->movingRightFirst();
        }
        else {
            saw->setSpeed(15.0f);
            saw->movingLeftFirst();
        }

        saw->setPosition(_position.x, _position.y + 10);
        this->addChild(saw, 2);
        index++;
    }
    int indexPlatForm = 0;
    TMXObjectGroup* platformGroup = _gameMap->getObjectGroup("Platform");
    auto platformObjects = platformGroup->getObjects();
    for (const auto& object : platformObjects) {
        ValueMap platformSpawnPoint = object.asValueMap();
        Vec2 _position;
        _position.x = platformSpawnPoint["x"].asFloat();
        _position.y = platformSpawnPoint["y"].asFloat();
        auto platform = Platform::create(new EntityInfo("platform"));
        if (indexPlatForm == 0) {
            platform->setSpeed(35.0f);
            platform->movingLeftFirst();
        }
        else if (indexPlatForm == 1) {
            platform->setSpeed(14.0f);
            platform->movingRightFirst();
        }
        else {
            platform->setSpeed(10.0f);
            platform->movingLeftFirst();
        }

        platform->setPosition(_position);
        this->addChild(platform, 2);
        indexPlatForm++;
    }
}

void BaseMap::addScore()
{
    auto _score = Score::getInstance();
    this->addChild(_score, 2);
}

void BaseMap::addTime()
{
    auto _time = Time::getInstance();
    this->addChild(_time, 2);
}


