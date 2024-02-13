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
            auto physicsBodyGround = PhysicsBody::createBox(Size(width, height), PhysicsMaterial(0, 0, 0));
            physicsBodyGround->setPositionOffset(Vec2(width * 0.5f, height * 0.5f));
            physicsBodyGround->setDynamic(false);
            groundNode->setPhysicsBody(physicsBodyGround);
            groundNode->setPosition(origin);
            this->addChild(groundNode);

            auto circleLeftPoint = Node::create();
            auto physicBodyLeftPoint = PhysicsBody::createCircle(0.4f, PhysicsMaterial(1, 1, 0));
            physicBodyLeftPoint->setDynamic(false);
            circleLeftPoint->setPhysicsBody(physicBodyLeftPoint);
            circleLeftPoint->setPosition(topLeft.x, topLeft.y - 0.5f);
            this->addChild(circleLeftPoint);

            auto circleRightPoint = Node::create();
            auto physicBodyRightPoint = PhysicsBody::createCircle(0.4f, PhysicsMaterial(1, 1, 0));
            physicBodyRightPoint->setDynamic(false);
            circleRightPoint->setPhysicsBody(physicBodyRightPoint);
            circleRightPoint->setPosition(topRight.x, topRight.y - 0.5f);
            this->addChild(circleRightPoint);

            auto topGroundNode = Node::create();
            auto physicsTopGround = PhysicsBody::createEdgeSegment(Vec2(topLeft.x + 1.5f, topLeft.y),
                Vec2(topRight.x - 1.5f, topRight.y), PhysicsMaterial(0, 0, 0), 0.1f);
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









