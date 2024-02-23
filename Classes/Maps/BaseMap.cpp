#include "BaseMap.h"
#include "ButtonController/ButtonController.h"
#include "Character/Character.h"
#include "MapUtilities/GameMap.h"
#include "PhysicRender/PhysicGround.h"
#include "Enemy/Enemy.h"
#include "PhysicRender/Stair.h"
#include "PhysicRender/Finish.h"
#include "Scene/GameScene.h"
#include "Scene/PauseGame.h"

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
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Vector<MenuItem*> MenuItems;
    auto miFont = MenuItemFont::create("Back", [&](Ref* sender) {
        auto gameScene = GameScene::create();
        Director::getInstance()->replaceScene(gameScene);
        log("Game Clicked");
        });
    miFont->setPosition(Vec2(150,60));
    MenuItems.pushBack(miFont);
    auto menuA = Menu::createWithArray(MenuItems);
    this->addChild(menuA, 2);
    /*auto pauseLayer = PauseLayer::create();
    this->addChild(pauseLayer, INT_MAX);*/
}

void BaseMap::createButtonController() {
    
    auto _buttonController = ButtonController::getInstance();
    this->addChild(_buttonController);
}

void BaseMap::createGroundPhysics() {
    auto objectPhysic = _gameMap->getObjectGroup("PhysicsObject");
    auto groundPhysics = PhysicGround::create(objectPhysic);
    this->addChild(groundPhysics);
}

void BaseMap::addCharacter() {

    EntityInfo* _characterInfo = new EntityInfo(1, "character");
    auto _characterInstance = Character::getInstance(_characterInfo);
    _characterInstance->addCharacter(_characterInfo);
    auto _character = _characterInstance->getCharacter(0);
    TMXObjectGroup* objectGroup = _gameMap->getObjectGroup("CharacterSpawnPoint");
    ValueMap charSpawnPoint = objectGroup->getObject("SpawnPoint");
    Vec2 _position;
    _position.x = charSpawnPoint["x"].asFloat();
    _position.y = charSpawnPoint["y"].asFloat();
    _character->setPosition(_position);
    this->addChild(_character,1);
}

void BaseMap::addBackground(const std::string& backgroundImagePath) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto _background = Sprite::create(backgroundImagePath);
    _background->setPosition(visibleSize / 2);
    _background->setScale(2.25f);
    this->addChild(_background);
}

void BaseMap::addEnemies() {
    std::vector<EntityInfo*> enemyInfoList;
    for (int i = 0; i < 2; i++) {
        EntityInfo* enemyInfo = new EntityInfo(1, "Hero");
        enemyInfoList.push_back(enemyInfo);
        auto _enemy = Enemy::getInstance(enemyInfo);
        _enemy->addEnemy(enemyInfo);
        auto enemyInstance = _enemy->getEnemy(i);

        float xPos = (600) + 100 * i;
        enemyInstance->setPosition(Vec2(200,200));
        //this->addChild(enemyInstance, 2);
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
