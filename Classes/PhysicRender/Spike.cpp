#include "Spike.h"
#include "Character/Character.h"
#include "DefineBitmask.h"

USING_NS_CC;


bool Spike::init(TMXObjectGroup* objectGroup)
{
	if (!Node::init()) {
		return false;
	}
	if (objectGroup)
	{
		auto objects = objectGroup->getObjects();
		for (const auto& object : objects)
		{
			ValueMap lineInfo = object.asValueMap();
			float x = lineInfo["x"].asFloat();
			float y = lineInfo["y"].asFloat();
			float width = lineInfo["width"].asFloat();
			float height = lineInfo["height"].asFloat();
			Vec2 origin(x, y);
			Vec2 topLeft(x, y + height);
			Vec2 topRight(x + width, y + height);

			auto spikeNode = Node::create();
			auto physicsSpikeNode = PhysicsBody::createBox(Size(width, height), PhysicsMaterial(1, 0, 0));
			physicsSpikeNode->setCategoryBitmask(DefineBitmask::SPIKE);
			physicsSpikeNode->setCollisionBitmask(DefineBitmask::NON);
			physicsSpikeNode->setContactTestBitmask(DefineBitmask::CHARACTER);
			physicsSpikeNode->setPositionOffset(Vec2(width * 0.5f, height * 0.5f));
			physicsSpikeNode->setDynamic(false);
			spikeNode->setPhysicsBody(physicsSpikeNode);
			spikeNode->setPosition(origin);
			this->addChild(spikeNode);
		}
	}
	return true;
}


Spike* Spike::create(TMXObjectGroup* objectGroup)
{
	auto ground = new (std::nothrow) Spike();
	if (ground && ground->init(objectGroup)) {
		ground->autorelease();
		return ground;
	}
	else {
		delete ground;
		return nullptr;
	}
}