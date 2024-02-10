#include "Entity.h"

Entity* Entity::create(EntityInfo* info)
{
    auto newObject = new Entity();
    if (newObject != nullptr && newObject->init(info))
    {
        newObject->autorelease();
        return newObject;
    }

    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Entity::init(EntityInfo* info)
{
    if (!Node::init())
    {
        log("Init Entity failed!");
        return false;
    }
    this->_info = info;
    loadAnimations();
    return true;
}

bool Entity::loadAnimations()
{
    return false;
}
