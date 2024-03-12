#include "CheckPoint.h"
#include "Character/Character.h"
#include "DefineBitmask.h"

USING_NS_CC;

bool CheckPoint::init(TMXObjectGroup* objectGroup) {
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

            auto checkPointNode = Node::create();
            auto physicsCheckPointNode = PhysicsBody::createBox(Size(width, height), PhysicsMaterial(1, 0, 0));
            physicsCheckPointNode->setCategoryBitmask(DefineBitmask::CHECKPOINT);
            physicsCheckPointNode->setCollisionBitmask(DefineBitmask::NON);
            physicsCheckPointNode->setContactTestBitmask(DefineBitmask::CHARACTER);
            physicsCheckPointNode->setPositionOffset(Vec2(width * 0.5f, height * 0.5f));
            physicsCheckPointNode->setDynamic(false);
            checkPointNode->setPhysicsBody(physicsCheckPointNode);
            checkPointNode->setPosition(origin);
            this->addChild(checkPointNode, 2);

            auto _model = Sprite::create("CheckPoint/checkpoint.png");
            Vec2 _position = Vec2(checkPointNode->getPositionX() + 16, checkPointNode->getPositionY() + 16);
            _model->setPosition(_position);
            this->addChild(_model);
            checkPointNode->setTag(++checkpointCount);
        }
    }

    return true;
}


CheckPoint* CheckPoint::create(TMXObjectGroup* objectGroup) {
    auto ground = new (std::nothrow) CheckPoint();
    if (ground && ground->init(objectGroup)) {
        ground->autorelease();
        return ground;
    }
    else {
        delete ground;
        return nullptr;
    }
}









