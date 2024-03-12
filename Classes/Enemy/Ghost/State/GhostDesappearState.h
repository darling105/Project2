#ifndef __GHOST_DESAPPEAR_STATE_H__
#define __GHOST_DESAPPEAR_STATE_H__

#include "StateMachine/State.h"

class GhostDesappearState : public State
{
public:
	void enterState(Entity* owner) override;
	std::string updateState() override;
	void exitState() override;
protected:
};

#endif // !__GHOST_DESAPPEAR_STATE_H__