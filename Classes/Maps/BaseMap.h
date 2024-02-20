#pragma once

#include "cocos2d.h"
#include "Character/Character.h"

class BaseMap : public cocos2d::Scene {
public:
    virtual bool init();
    void addBackground(const std::string& backgroundImagePath);
    void addCharacter();
    void addEnemies();
    void addGameMap(const std::string& gameMapPath);
    void addLadder();
    GameMap* _gameMap;
protected:
    cocos2d::PhysicsWorld* _physicsWorld;
    std::vector<cocos2d::Node*> _enemies;

    CREATE_FUNC(BaseMap);

    void createPhysicsWorld();
    void createMenu();
    void createButtonController();
    void createGroundPhysics();
};
