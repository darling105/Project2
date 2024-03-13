#ifndef __TINY_JUMP_STATE_H__
#define __TINY_JUMP_STATE_H__

#include "StateMachine/State.h"

class TinyJumpState : public State
{
public:
	void enterState(Entity* owner) override;
	std::string updateState() override;
	void exitState() override;
};

#endif // !__TINY_JUMP_STATE_H__