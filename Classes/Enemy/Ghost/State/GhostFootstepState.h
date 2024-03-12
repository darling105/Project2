#ifndef __GHOST_FOOT_STEP_STATE_H__
#define __GHOST_FOOT_STEP_STATE_H__

#include "StateMachine/State.h"

class GhostFootstepState : public State
{
public:
	void enterState(Entity* owner) override;
	std::string updateState() override;
	void exitState() override;
protected:
};

#endif // !__GHOST_FOOT_STEP_STATE_H__