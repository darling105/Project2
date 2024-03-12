#ifndef __WILLIAM_IDLE_STATE_H__
#define __WILLIAM_IDLE_STATE_H__

#include "StateMachine/State.h"


class WilliamIdleState : public State
{
public:
	void enterState(Entity* owner) override;
	std::string updateState() override;
	void exitState() override;
};

#endif // !__WILLIAM_IDLE_STATE_H__
