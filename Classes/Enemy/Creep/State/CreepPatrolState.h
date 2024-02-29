#ifndef __CREEP_PATROL_STATE_H__
#define __CREEP_PATROL_STATE_H__

#include "StateMachine/State.h"
#include "Character/Character.h"
class CreepPatrolState : public State
{
public:
	void enterState(Entity* owner) override;
	std::string updateState() override;
	void exitState() override;
protected:
	bool movingRight = false;
	bool movingLeft = false;
};

#endif // !__CREEP_PATROL_STATE_H__