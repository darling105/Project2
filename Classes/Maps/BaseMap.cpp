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
    //_physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    _physicsWorld->setGravity(Vec2(0, -600));
    _physicsWorld->setFixedUpdateRate(600.0f);
}

void BaseMap::createMenu() {
    
}

void BaseMap::createButtonController() {

    auto _buttonController1 = ButtonController::getInstance();
    this->addChild(_buttonController1);
}

void BaseMap::createGroundPhysics() {
    auto objectPhysic = _gameMap->getObjectGroup("PhysicsObject");
    auto groundPhysics = PhysicGround::create(objectPhysic);
    this->addChild(groundPhysics);
}

void BaseMap::createPolygonPhysics()
{
    auto objectPolygon = _gameMap->getObjectGroup("PolygonPhysicsObject");
    auto polygonPhysics = PolygonGround::create(objectPolygon);
    this->addChild(polygonPhysics);
}

void BaseMap::createHealthBar()
{
    auto _healthBar = HealthController::getInstance(3, "Character/Health/Healthbar_full.png");
    _healthBar->setScale(2.0f);
    _healthBar->setPosition(2400, 1200);
    this->addChild(_healthBar, 3);

    auto _healthEmpty = HealthBarEmpty::getInstance("Character/Health/Healthbar_empty.png");
    _healthEmpty->setScale(2.0f);
    _healthEmpty->setPosition(2400, 1200);
    this->addChild(_healthEmpty, 2);
}

void BaseMap::addCharacter() {

    EntityInfo* _characterInfo = new EntityInfo("character");
    auto _characterInstance = Character::getInstance(_characterInfo);
    _characterInstance->addCharacter(_characterInfo);
    auto _character = _characterInstance->getCharacter(0);
    TMXObjectGroup* objectGroup = _gameMap->getObjectGroup("CharacterSpawnPoint");
    ValueMap charSpawnPoint = objectGroup->getObject("SpawnPoint");
    Vec2 _position;
    _position.x = charSpawnPoint["x"].asFloat();
    _position.y = charSpawnPoint["y"].asFloat();
    _character->setPosition(_position);
    this->addChild(_character, 1);
}

void BaseMap::addBackground(const std::string& backgroundImagePath) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto _background = Sprite::create(backgroundImagePath);
    _background->setPosition(visibleSize / 2);
    _background->setScale(2.25f);
    this->addChild(_background);
}

void BaseMap::addEnemies() {
    int numEnemies = 3;
    int index = 0;

        TMXObjectGroup* puppleObjectGroup = _gameMap->getObjectGroup("PuppleSpawnPoint");
        auto puppleObjects = puppleObjectGroup->getObjects();
        for (const auto& object : puppleObjects) {
            ValueMap puppleSpawnPoint = object.asValueMap();
            Vec2 _position;
            _position.x = puppleSpawnPoint["x"].asFloat();
            _position.y = puppleSpawnPoint["y"].asFloat();
            auto pupple = Pupple::create(new EntityInfo("pupple"));
            pupple->setPosition(_position);
            //this->addChild(pupple, 2);
            auto creep = Creep::create(new EntityInfo("creep"));
            creep->setPosition(_position);
            this->addChild(creep, 2);
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
            this->addChild(_void, 2);
        }
    
        TMXObjectGroup* objectGroup = _gameMap->getObjectGroup("BatSpawnPoint");
        auto objects = objectGroup->getObjects();
        int batIndex = 0; // Số thứ tự của con dơi
        for (const auto& object : objects) {
            ValueMap batSpawnPoint = object.asValueMap();
            Vec2 _position;
            _position.x = batSpawnPoint["x"].asFloat();
            _position.y = batSpawnPoint["y"].asFloat();
            bat = Bat::create(new EntityInfo("bat"));
            bat->setPosition(_position);
            if (batIndex == 1) {
                bat->setupBat(80, Vec2(-1, 0));
            }
            else {
                bat->setupBat(80, Vec2(1, 0));
            }
            this->addChild(bat, 2);
            batIndex++;
        }


}

void BaseMap::addGameMap(const std::string& gameMapPath)
{
    _gameMap = GameMap::create(gameMapPath);
    this->addChild(_gameMap);
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