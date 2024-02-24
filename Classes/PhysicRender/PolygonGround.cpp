#include "PolygonGround.h"
#include "Character/Character.h"
#include "DefineBitmask.h"

USING_NS_CC;
using namespace std;

PolygonGround* PolygonGround::create(TMXObjectGroup* objectGroup) {
    auto ground = new (std::nothrow) PolygonGround();
    if (ground && ground->init(objectGroup)) {
        ground->autorelease();
        return ground;
    }
    else {
        delete ground;
        return nullptr;
    }
}

bool PolygonGround::init(TMXObjectGroup* objectGroup)
{
    if (!Node::init()) {
        return false;
    }

    auto objects = objectGroup->getObjects();
    for (const auto& object : objects) {
        ValueMap objectProperties = object.asValueMap();
        auto points = objectProperties["points"].asValueVector();
        std::vector<Vec2> originalPolygonPoints;
        for (const auto& pointValue : points) {
            ValueMap pointMap = pointValue.asValueMap();
            float x = pointMap["x"].asFloat();
            float y = pointMap["y"].asFloat();
            originalPolygonPoints.push_back(Vec2(x, y));
        }

        std::vector<Vec2> reversedPolygonPoints;
        for (const auto& point : originalPolygonPoints) {
            reversedPolygonPoints.push_back(Vec2(point.x, -point.y));
        }

        auto groundNode = Node::create();
        auto physicsBodyGround = PhysicsBody::createPolygon(reversedPolygonPoints.data(), static_cast<int>(reversedPolygonPoints.size()));
        physicsBodyGround->setCategoryBitmask(DefineBitmask::GROUND);
        physicsBodyGround->setCollisionBitmask(DefineBitmask::CHARACTER);
        physicsBodyGround->setContactTestBitmask(DefineBitmask::CHARACTER);
        physicsBodyGround->setDynamic(false);
        groundNode->setPhysicsBody(physicsBodyGround);

        float x = objectProperties["x"].asFloat();
        float y = objectProperties["y"].asFloat();
        groundNode->setPosition(Vec2(x, y));

        groundNode->setTag(TAG_GROUND);

        this->addChild(groundNode);
    }

    return true;
}

