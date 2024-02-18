#include "Skill.h"
#include "DefineBitmask.h"
#include "AnimationUtilities/AnimationUtils.h"

//#include "IDamageable.h"

Skill* Skill::create(std::string skillName)
{
	auto newObject = new Skill();
	if (newObject != nullptr && newObject->init(skillName)) {
		newObject->autorelease();
		return newObject;
	}
	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool Skill::init(std::string skillName)
{
    if (!Node::init()) {
        return false;
    }

    // Tải sprite frame cache từ file plist và texture
    if (!AnimationUtils::loadSpriteFrameCache("/Skill/", skillName)) {
        log("Failed to load sprite frame cache");
        return false;
    }

    // Tạo animation từ sprite frame cache
    auto animationInfo = AnimationUtils::createAnimation(skillName, 1.0f); // Đặt thời gian cho mỗi frame
    auto animation = animationInfo.first;
    auto numFrames = animationInfo.second;

    // Tạo animate từ animation
    auto animate = RepeatForever::create(Animate::create(animation));

    // Tạo sprite và chạy animation
    _model = Sprite::createWithSpriteFrameName("./" + skillName + " (1)");
    _model->setAnchorPoint(Vec2(0.6, 0.3));
    _model->runAction(animate);
    this->addChild(_model, 5);

    // Tạo physics body cho đạn
    auto bodyBullet = PhysicsBody::createCircle(_model->getContentSize().height / 4, PhysicsMaterial(1, 0, 1));
    bodyBullet->setContactTestBitmask(DefineBitmask::BULLET);
    bodyBullet->setCollisionBitmask(DefineBitmask::GROUND);
    bodyBullet->setTag(SKILL_TAG);
    this->setPhysicsBody(bodyBullet);

    // Thêm listener cho sự kiện va chạm
    auto listener = EventListenerPhysicsContact::create();
    listener->onContactBegin = CC_CALLBACK_1(Skill::callbackOnContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}




bool Skill::callbackOnContactBegin(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA != this && nodeB != this) return false;

	auto target = (nodeA == this) ? (nodeB) : (nodeA);

	/*log("a: %d | b: %d", nodeA->getPhysicsBody()->getCategoryBitmask()
		, nodeB->getPhysicsBody()->getCategoryBitmask());
	log("a & b: %d", (nodeA->getPhysicsBody()->getCategoryBitmask() | nodeB->getPhysicsBody()->getCategoryBitmask()));*/

	/*auto damageable = dynamic_cast<IDamageable*>(target);
	if (damageable != nullptr)
	{
		damageable->takeDamage(_owner);
	}*/

	//this->removeFromParentAndCleanup(true);

	return false;
}


