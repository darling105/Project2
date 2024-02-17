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

Scene* Map1::create()
{
	auto newObject = new Map1();
	if (newObject != nullptr && newObject->init())
	{
		newObject->autorelease();
		return newObject;
	}
	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool Map1::init()
{
    if (!Scene::initWithPhysics())
    {
        return false;
    }

    removeAllChildren();
    Vec2 origin = Director::getInstance()->getVisibleSize();
    auto physicsWorld = this->getPhysicsWorld();
    this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    this->getPhysicsWorld()->setGravity(Vec2(0, -400));
    physicsWorld->setFixedUpdateRate(1000.0f);
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // Tạo menu "Back"
    auto miFont = MenuItemFont::create("Back", [&](Ref* sender) {
        auto gameScene = GameScene::create();
        Director::getInstance()->replaceScene(gameScene);
        this->resetInput();
        log("Back button clicked");
        });
    auto menuA = Menu::create(miFont, nullptr);
    menuA->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2 ));
    this->addChild(menuA, 3);

    // Thêm Background
    auto _background = Sprite::create("BackGround/Background2.png");
    _background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    _background->setScale(2.25f);
    this->addChild(_background);

    // Thêm GameMap
    _gameMap = GameMap::create("Map/map1.tmx");
    this->addChild(_gameMap, 1);

    // Khởi tạo Character
    EntityInfo* characterInfo = new EntityInfo(1, "character");
    _character = Character::getInstance(characterInfo);
    _character->addCharacter(characterInfo);
    auto _charInstance = _character->getCharacter(0);
    TMXObjectGroup* objectGroup = _gameMap->getObjectGroup("CharacterSpawnPoint");
    ValueMap charSpawnPoint = objectGroup->getObject("SpawnPoint");
    Vec2 position;
    position.x = charSpawnPoint["x"].asFloat();
    position.y = charSpawnPoint["y"].asFloat();
    _charInstance->setPosition(position);
    this->addChild(_charInstance, 2);

    std::vector<EntityInfo*> enemyInfoList;
    for (int i = 0; i < 5; i++) {
    EntityInfo* enemyInfo = new EntityInfo(1, "Hero");
    enemyInfoList.push_back(enemyInfo);
    _enemy = Enemy::getInstance(enemyInfo);
    _enemy->addEnemy(enemyInfo);
    auto enemyInstance = _enemy->getEnemy(i);

    float xPos = (600) + 100 * i;
    enemyInstance->setPosition(Vec2(xPos, position.y));
    //this->addChild(enemyInstance);
    }
   _buttonController = ButtonController::create();
    this->addChild(_buttonController,3);
    
    auto objectPhysic = _gameMap->getObjectGroup("PhysicsObject");
    auto groundPhysics = PhysicGround::create(objectPhysic);
    this->addChild(groundPhysics);

    auto objectLadder = _gameMap->getObjectGroup("Ladder");
    auto groundLadder = Stair::create(objectLadder);
    this->addChild(groundLadder);

    auto _char = _character->getCharacter(0);
    Size size = Director::getInstance()->getOpenGLView()->getFrameSize();
    auto mapSize = _gameMap->getContentSize();
    Rect boundingBox = { size.width / 2,size.height / 2,1280 - size.width / 2 - size.width / 2,896 - size.height / 2 - size.height / 2 };
    cam = CameraFollow::create(_char, boundingBox);
    this->addChild(cam);

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
    
   /* log("min x:%f", boundingBox.getMinX());
    log("max x:%f", boundingBox.getMaxX());
    log("min y:%f", boundingBox.getMinY());
    log("max y:%f", boundingBox.getMaxY());

    log("map x:%f", mapSize.width);
    log("map y:%f", mapSize.height);*/
   
    this->resetInput();
}

void Map1::resetInput()
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->removeEventListenersForTarget(this);
}
void Map1::update(float dt)
{
    // Kiểm tra xem camera có thay đổi vị trí không
    if (cam && cam->isDirty()) {
        // Lấy vị trí mới của camera
        auto camPosition = cam->getPosition();
        // Cập nhật vị trí của ButtonController theo vị trí mới của camera
        _buttonController->setPosition(camPosition);
    }
}








