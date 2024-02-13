#include "Map1.h"
#include "Scene/GameScene.h"
#include "MapUtilities/GameMap.h"
#include "StateMachine/StateMachine.h"
#include "Character/Character.h";
#include "ButtonController/ButtonController.h"
#include "PhysicRender/PhysicGround.h"



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

    

    auto physicsWorld = this->getPhysicsWorld();
    this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    this->getPhysicsWorld()->setGravity(Vec2(0, -400));
    physicsWorld->setFixedUpdateRate(800.0f);
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // Tạo menu "Back"
    auto miFont = MenuItemFont::create("Back", [&](Ref* sender) {
        auto gameScene = GameScene::create();
        Director::getInstance()->replaceScene(gameScene);
        log("Back button clicked");
        });
    auto menuA = Menu::create(miFont, nullptr);
    menuA->setPosition(Vec2(visibleSize.width / 2 - 1100, visibleSize.height / 2 - 50));
    this->addChild(menuA, 1);

    // Thêm Background
    auto _background = Sprite::create("BackGround/Background2.png");
    _background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    _background->setScale(2.25f);
    this->addChild(_background);

    // Thêm GameMap
    auto map1 = GameMap::create("Map/map1.tmx");
    this->addChild(map1, 1);

    // Khởi tạo Character
    EntityInfo* characterInfo = new EntityInfo(1, "character");
    auto _characterInstance = Character::getInstance(characterInfo);
    _characterInstance->addCharacter(characterInfo);
    auto _character = _characterInstance->getCharacter(0);
    TMXObjectGroup* objectGroup = map1->getObjectGroup("CharacterSpawnPoint");
    ValueMap charSpawnPoint = objectGroup->getObject("SpawnPoint");
    Vec2 position;
    position.x = charSpawnPoint["x"].asFloat();
    position.y = charSpawnPoint["y"].asFloat();
    _character->setPosition(position);
    this->addChild(_character, 2);

    auto buttonController = ButtonController::create();
    this->addChild(buttonController);
    

    auto objectPhysic = map1->getObjectGroup("PhysicsObject");
    auto groundPhysics = PhysicGround::create(objectPhysic);
    this->addChild(groundPhysics);

    this->scheduleUpdate();

    return true;
}


void Map1::goToGameScene()
{
	Director::getInstance()->popScene();
}
