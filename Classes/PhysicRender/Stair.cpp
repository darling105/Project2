#include "Stair.h"
#include "Character/Character.h"
#include "DefineBitmask.h"

USING_NS_CC;


bool Stair::init(TMXObjectGroup* objectGroup) {
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

            auto stairNode = Node::create();
            auto physicsStairNode = PhysicsBody::createBox(Size(width, height), PhysicsMaterial(1, 0, 0));
            physicsStairNode->setCategoryBitmask(DefineBitmask::LADDER);
            physicsStairNode->setCollisionBitmask(DefineBitmask::CHARACTER);
            physicsStairNode->setContactTestBitmask(DefineBitmask::CHARACTER);
            physicsStairNode->setPositionOffset(Vec2(width * 0.5f, height * 0.5f));
            physicsStairNode->setDynamic(false);
            stairNode->setPhysicsBody(physicsStairNode);
            stairNode->setPosition(origin);
            this->addChild(stairNode);

        }
    }

    return true;
}



Stair* Stair::create(TMXObjectGroup* objectGroup) {
    auto ground = new (std::nothrow) Stair();
    if (ground && ground->init(objectGroup)) {
        ground->autorelease();
        return ground;
    }
    else {
        delete ground;
        return nullptr;
    }
}









