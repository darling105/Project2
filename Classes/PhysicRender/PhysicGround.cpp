#include "PhysicGround.h"
#include "Character/Character.h"
#include "DefineBitmask.h"

USING_NS_CC;


bool PhysicGround::init(TMXObjectGroup* objectGroup) {
    if (!Node::init()) {
        return false;
    }

    if (objectGroup) {
        auto objects = objectGroup->getObjects();
        for (const auto& object : objects) {
            ValueMap lineInfo = object.asValueMap();
            float x = lineInfo["x"].asFloat();
            float y = lineInfo["y"].asFloat();
            float width = lineInfo["width"].asFloat();
            float height = lineInfo["height"].asFloat();
            Vec2 origin(x, y);
            Vec2 topLeft(x, y + height);
            Vec2 topRight(x + width, y + height);
            auto groundNode = Node::create();
            auto physicsBodyGround = PhysicsBody::createBox(Size(width, height), PhysicsMaterial(1, 0, 0));
            physicsBodyGround->setPositionOffset(Vec2(width * 0.5f, height * 0.5f));
            physicsBodyGround->setDynamic(false);
            groundNode->setPhysicsBody(physicsBodyGround);
            groundNode->setPosition(origin);
            this->addChild(groundNode);

            auto topGroundNode = Node::create();
            auto physicsTopGround = PhysicsBody::createEdgeSegment(Vec2(topLeft.x + 3.0f, topLeft.y),
                Vec2(topRight.x - 3.0f, topRight.y), PhysicsMaterial(1, 0, 1), 2.0f);
            physicsTopGround->setCategoryBitmask(DefineBitmask::GROUND);
            physicsTopGround->setCollisionBitmask(DefineBitmask::CHARACTER);
            physicsTopGround->setContactTestBitmask(DefineBitmask::CHARACTER);
            topGroundNode->setPhysicsBody(physicsTopGround);
            topGroundNode->setTag(TAG_GROUND);
            this->addChild(topGroundNode);
        }
    }

    return true;
}

 

PhysicGround* PhysicGround::create(TMXObjectGroup* objectGroup) {
    auto ground = new (std::nothrow) PhysicGround();
    if (ground && ground->init(objectGroup)) {
        ground->autorelease();
        return ground;
    }
    else {
        delete ground;
        return nullptr;
    }
}









