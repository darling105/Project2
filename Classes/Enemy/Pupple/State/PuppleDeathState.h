#ifndef __PUPPLE_DEATH_STATE_H__
#define __PUPPLE_DEATH_STATE_H__

#include "StateMachine/State.h"

class PuppleDeathState : public State
{
public:
	void enterState(Entity* owner) override;
	std::string updateState() override;
	void exitState() override;
protected:

};

#endif // !__PUPPLE_DEATH_STATE_H__