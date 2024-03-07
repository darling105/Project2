#ifndef __BAT_PATROL_STATE_H__
#define __BAT_PATROL_STATE_H__

#include "StateMachine/State.h"
#include "Character/Character.h"
class BatPatrolState : public State
{
public:
	void enterState(Entity* owner) override;
	std::string updateState() override;
	void exitState() override;
protected:
	void movingLeftFirst();
	void movingRightFirst();
protected:
	bool movingRight = false;
	bool movingLeft = false;
};

#endif // !__BAT_PATROL_STATE_H__