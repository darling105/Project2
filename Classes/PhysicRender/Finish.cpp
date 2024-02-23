#include "Finish.h"
#include "Character/Character.h"
#include "DefineBitmask.h"

USING_NS_CC;


bool Finish::init(TMXObjectGroup* objectGroup) {
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

            auto finishNode = Node::create();
            auto physicsFinishNode = PhysicsBody::createBox(Size(width, height), PhysicsMaterial(1, 0, 0));
            physicsFinishNode->setCategoryBitmask(DefineBitmask::FINISH);
            physicsFinishNode->setCollisionBitmask(DefineBitmask::NON);
            physicsFinishNode->setContactTestBitmask(DefineBitmask::CHARACTER);
            physicsFinishNode->setPositionOffset(Vec2(width * 0.5f, height * 0.5f));
            physicsFinishNode->setDynamic(false);
            finishNode->setPhysicsBody(physicsFinishNode);
            finishNode->setPosition(origin);
            this->addChild(finishNode);

        }
    }

    return true;
}



Finish* Finish::create(TMXObjectGroup* objectGroup) {
    auto ground = new (std::nothrow) Finish();
    if (ground && ground->init(objectGroup)) {
        ground->autorelease();
        return ground;
    }
    else {
        delete ground;
        return nullptr;
    }
}









