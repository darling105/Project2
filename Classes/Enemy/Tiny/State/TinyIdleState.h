#ifndef __TINY_IDLE_STATE_H__
#define __TINY_IDLE_STATE_H__

#include "StateMachine/State.h"

class TinyIdleState : public State
{
public:
	void enterState(Entity* owner) override;
	std::string updateState() override;
	void exitState() override;
};

#endif // !__TINY_IDLE_STATE_H__