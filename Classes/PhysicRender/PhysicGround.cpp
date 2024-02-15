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
            Vec2 bottomLeft(x, y);
            Vec2 bottomRight(x + width, y);

            /*Vec2 bottomLeftToTopLeft = topLeft - bottomLeft;
            Vec2 newBottomLeft = bottomLeft + bottomLeftToTopLeft * 0.2f;
            Vec2 bottomRightToTopRight = topRight - bottomRight;
            Vec2 newBottomRight = bottomRight + bottomRightToTopRight * 0.2f;
            Vec2 topLeftToBottomLeft = bottomLeft - topLeft;
            Vec2 newTopLeft = topLeft + topLeftToBottomLeft * 0.2f;
            Vec2 topRightToBottomRight = bottomRight - topRight;
            Vec2 newTopRight = topRight + topRightToBottomRight * 0.2f;*/


            auto groundNode = Node::create();
            auto physicsBodyGround = PhysicsBody::createBox(Size(width, height), PhysicsMaterial(1, 0, 0));
            physicsBodyGround->setCategoryBitmask(DefineBitmask::GROUND);
            physicsBodyGround->setCollisionBitmask(DefineBitmask::CHARACTER);
            physicsBodyGround->setContactTestBitmask(DefineBitmask::CHARACTER);
            physicsBodyGround->setPositionOffset(Vec2(width * 0.5f, height * 0.5f));
            physicsBodyGround->setDynamic(false);
            groundNode->setPhysicsBody(physicsBodyGround);
            groundNode->setPosition(origin);
            groundNode->setTag(TAG_GROUND);
            this->addChild(groundNode);

            /*auto circleBottomLeftPoint = Node::create();
            auto physicBodyBottomLeftPoint = PhysicsBody::createCircle(1.0f, PhysicsMaterial(0, 1, 0));
            physicBodyBottomLeftPoint->setDynamic(false);
            circleBottomLeftPoint->setPhysicsBody(physicBodyBottomLeftPoint);
            circleBottomLeftPoint->setPosition(bottomLeft.x + 0.3f, bottomLeft.y - 0.5f);
            this->addChild(circleBottomLeftPoint);

            auto circleTopLeftPoint = Node::create();
            auto physicBodyTopLeftPoint = PhysicsBody::createCircle(1.0f, PhysicsMaterial(0, 1, 0));
            physicBodyTopLeftPoint->setDynamic(false);
            circleTopLeftPoint->setPhysicsBody(physicBodyTopLeftPoint);
            circleTopLeftPoint->setPosition(topLeft.x + 0.3f, bottomLeft.y - 0.5f);
            this->addChild(circleTopLeftPoint);

            auto circleBottomRightPoint = Node::create();
            auto physicBodyBottomRightPoint = PhysicsBody::createCircle(1.0f, PhysicsMaterial(0, 1, 0));
            physicBodyBottomRightPoint->setDynamic(false);
            circleBottomRightPoint->setPhysicsBody(physicBodyBottomRightPoint);
            circleBottomRightPoint->setPosition(bottomRight.x - 0.3f, bottomRight.y - 0.5f);
            this->addChild(circleBottomRightPoint);

            auto circleTopRightPoint = Node::create();
            auto physicBodyTopRightPoint = PhysicsBody::createCircle(1.0f, PhysicsMaterial(0, 1, 0));
            physicBodyTopRightPoint->setDynamic(false);
            circleTopRightPoint->setPhysicsBody(physicBodyTopRightPoint);
            circleTopRightPoint->setPosition(topRight.x - 0.3f, topRight.y - 0.5f);
            this->addChild(circleTopRightPoint);*/

            /*auto topGroundNode = Node::create();
            auto physicsTopGround = PhysicsBody::createEdgeSegment(Vec2(topLeft.x + 0.0f, topLeft.y),
                Vec2(topRight.x - 0.0f, topRight.y), PhysicsMaterial(0, 0, 0), 0.1f);
            physicsTopGround->setCategoryBitmask(DefineBitmask::GROUND);
            physicsTopGround->setCollisionBitmask(DefineBitmask::CHARACTER);
            physicsTopGround->setContactTestBitmask(DefineBitmask::CHARACTER);
            topGroundNode->setPhysicsBody(physicsTopGround);
            topGroundNode->setTag(TAG_GROUND);
            this->addChild(topGroundNode);*/
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