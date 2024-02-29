#ifndef __CHARACTER_CLIMB_STATE_H__
#define __CHARACTER_CLIMB_STATE_H__

#include "StateMachine/State.h"


class CharacterClimbState : public State
{
public:
	void enterState(Entity* owner) override;
	std::string updateState() override;
	void exitState() override;
};

#endif // !__CHARACTER_CLIMB_STATE_H__