#ifndef __CHARACTER_IDLE_STATE_H__
#define __CHARACTER_IDLE_STATE_H__

#include "State.h"


class CharacterIdleState : public State
{
public:
	void enterState(Entity* owner) override;
	std::string updateState() override;
	void exitState() override;
};

#endif // !__CHARACTER_IDLE_STATE_H__
