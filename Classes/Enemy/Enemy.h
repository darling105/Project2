#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity/Entity.h"
#include "StateMachine/StateMachine.h"
#include "State/EnemyChaseState.h"
#include "State/EnemyIdleState.h"
#include "State/EnemyPatrolState.h"


class Enemy : public Entity
{
public:
	static const int ENEMY_TAG = 11;
	static Enemy* getInstance(EntityInfo* info);
	static void addEnemy(EntityInfo* info);
	static int getNumberOfEnemy();
	static Enemy* getEnemy(int index);
protected:
	static Enemy* _instance;
	static std::vector<Enemy*> _enemies;
	virtual bool init(EntityInfo* info) override;
	bool loadAnimations() override;
	StateMachine* _enemyStateMachine;
	bool callbackOnContactBegin(PhysicsContact& contact);
	//void shoot(float dt);
	void onEnter() override;
protected:
	Node* nodeA;
	Node* nodeB;
	Node* target;
	float timeSinceLastShot;

};
#endif // !__ENEMY_H__
