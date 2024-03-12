#ifndef __VOID_H__
#define __VOID_H__

#include "Entity/Entity.h"
#include "StateMachine/StateMachine.h"

class Void : public Entity
{
public:
	static const int ENEMY_TAG = 12;
	static Void* create(EntityInfo* info);
	virtual bool init(EntityInfo* info) override;
	void setupVoid(float rotation, float timeShoot, Vec2 skillDirection);
protected:
	bool loadAnimations() override;
	void update(float dt);
	void shoot(float dt);
	//void onEnter() override;
protected:
	StateMachine* _enemyStateMachine;
	Node* nodeA;
	Node* nodeB;
	Node* target;
	bool _isContactCharacter = false;
	float _timeShoot;
	float _countTime;
	float _rotation;
	Vec2 _skillDirection;


};
#endif // !__VOID_H__