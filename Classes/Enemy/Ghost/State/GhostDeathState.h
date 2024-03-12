#ifndef __GHOST_DEATH_STATE_H__
#define __GHOST_DEATH_STATE_H__

#include "StateMachine/State.h"

class GhostDeathState : public State
{
public:
	void enterState(Entity* owner) override;
	std::string updateState() override;
	void exitState() override;
protected:
};

#endif // !__GHOST_DEATH_STATE_H__