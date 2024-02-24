#ifndef __CREEP_H__
#define __CREEP_H__

#include "Entity/Entity.h"
#include "StateMachine/StateMachine.h"
#include "State/EnemyChaseState.h"
#include "State/EnemyIdleState.h"
#include "State/EnemyPatrolState.h"
#include "State/EnemyAttackState.h"


class Creep : public Entity
{
public:
	static const int ENEMY_TAG = 12;
	static Creep* getInstance(EntityInfo* info);
	static void addEnemy(EntityInfo* info);
	static int getNumberOfEnemy();
	static Creep* getEnemy(int index);
	bool _isAttack = false;
	bool _rightRange = false;
	bool _leftRange = false;
	void shoot(float dt);
protected:
	static Creep* _instance;
	static std::vector<Creep*> _enemies;
	virtual bool init(EntityInfo* info) override;
	bool loadAnimations() override;
	StateMachine* _enemyStateMachine;
	bool callbackOnContactBegin(PhysicsContact& contact);
	void onEnter() override;
	void update(float dt);

protected:
	Node* nodeA;
	Node* nodeB;
	Node* target;
	float timeSinceLastShot;
	float bulletTimer; 
	float bulletInterval; 
	float _distanceRight, _distanceLeft = 100.0f;

};
#endif // !__CREEP_H__
