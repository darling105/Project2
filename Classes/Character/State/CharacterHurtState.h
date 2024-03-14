#ifndef __CHARACTER_HURT_STATE_H__
#define __CHARACTER_HURT_STATE_H__

#include "StateMachine/State.h"


class CharacterHurtState : public State
{
public:
	void enterState(Entity* owner) override;
	std::string updateState() override;
	void exitState() override;
};

#endif // !__CHARACTER_HURT_STATE_H__
