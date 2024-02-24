#include "Bullet.h"
#include "DefineBitmask.h"

Bullet* Bullet::create(std::string bulletName)
{
	auto newObject = new Bullet();
	if (newObject != nullptr && newObject->init(bulletName))
	{
		newObject->autorelease();
		return newObject;
	}

	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool Bullet::init(std::string bulletName)
{
	if (!Node::init())
	{
		return false;
	}
	_model = Sprite::create("Skill/" + bulletName + ".png");
	this->addChild(_model);
	auto bodyBullet = PhysicsBody::createCircle(_model->getContentSize().height / 4, PhysicsMaterial(1, 0, 1));
	bodyBullet->setContactTestBitmask(DefineBitmask::BULLET);
	bodyBullet->setCollisionBitmask(DefineBitmask::GROUND);
	bodyBullet->setTag(SKILL_TAG);
	this->setPhysicsBody(bodyBullet);
    return true;
}

