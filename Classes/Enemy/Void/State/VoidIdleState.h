#ifndef __VOID_IDLE_STATE_H__
#define __VOID_IDLE_STATE_H__

#include "StateMachine/State.h"

class VoidIdleState : public State
{
public:
	void enterState(Entity* owner) override;
	std::string updateState() override;
	void exitState() override;
};

#endif // !__VOID_IDLE_STATE_H__
