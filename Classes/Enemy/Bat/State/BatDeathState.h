#ifndef __BAT_DEATH_STATE_H__
#define __BAT_DEATH_STATE_H__

#include "StateMachine/State.h"

class BatDeathState : public State
{
public:
	void enterState(Entity* owner) override;
	std::string updateState() override;
	void exitState() override;
protected:
};

#endif // !__BAT_PATROL_STATE_H__