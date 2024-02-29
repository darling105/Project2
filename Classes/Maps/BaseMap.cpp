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
    _physicsWorld->setGravity(Vec2(0, -400));
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
    int numEnemies = 1;
    for (int i = 0; i < numEnemies; i++) {

        TMXObjectGroup* objectGroup = _gameMap->getObjectGroup("VoidEnemySpawnPoint");
        ValueMap charSpawnPoint = objectGroup->getObject("SpawnPoint");
        Vec2 _position;
        _position.x = charSpawnPoint["x"].asFloat();
        _position.y = charSpawnPoint["y"].asFloat();

        auto _creep = Creep::create(new EntityInfo("creep"));
        auto _creep1 = Creep::create(new EntityInfo("creep"));
        _creep->setPosition(_position);
        _creep1->setPosition(_position.x + 400, _position.y);
        this->addChild(_creep, 2);
        this->addChild(_creep1, 2);

        auto bat = Bat::create(new EntityInfo("bat"));
        bat->setPosition(_position.x + 400, _position.y + 100);
        this->addChild(bat, 2);
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
    int numLargeSpawnCoin = 2;
    int numTinySpawnCoin = 1;
    int coinIndex = 0;
    for (int i = 0; i < 7; i++) {
        TMXObjectGroup* objectGroup = _gameMap->getObjectGroup("CoinSpawnPoint");
        for (int j = 0; j < numLargeSpawnCoin; j++) {
            ValueMap coinPoint = objectGroup->getObject("LargeCoinPoint" + std::to_string(j));
            Vec2 _position;
            _position.x = coinPoint["x"].asFloat();
            _position.y = coinPoint["y"].asFloat();
            auto coin = Coin::create(new EntityInfo("coin"));
            coin->setPosition(_position.x + 16 * (coinIndex + 1), _position.y + 16);
            this->addChild(coin, 2);
            coinIndex++;
        }
    }
    log("%d", coinIndex);
    // Thêm đồng xu cho TinyCoinSpawnPoint
    /*TMXObjectGroup* tinyCoinObjectGroup = _gameMap->getObjectGroup("TinyCoinSpawnPoint");
    auto objects = tinyCoinObjectGroup->getObjects();
    for (const auto& object : objects) {
        ValueMap lineInfo = object.asValueMap();
        Vec2 _position;
        _position.x = lineInfo["x"].asFloat();
        _position.y = lineInfo["y"].asFloat();
        coinInstance->addCoin(info);
        auto coin = coinInstance->getCoin(coinIndex);
        coin->setPosition(_position.x + 16, _position.y + 16);
        this->addChild(coin, 2);
        log("%d", coin->getNumberOfCoin());
        coinIndex++;*/
        //}
}
void BaseMap::addObjects()
{
    auto trampoline = Trampoline::create(new EntityInfo("trampoline"));
    trampoline->setPosition(Vec2(900, 1100));
    this->addChild(trampoline, 2);
}