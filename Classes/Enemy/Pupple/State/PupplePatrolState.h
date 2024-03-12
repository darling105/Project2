#ifndef __PUPPLE_PATROL_STATE_H__
#define __PUPPLE_PATROL_STATE_H__

#include "StateMachine/State.h"

class PupplePatrolState : public State
{
public:
	void enterState(Entity* owner) override;
	std::string updateState() override;
	void exitState() override;
protected:
	void movingLeftFirst();
	void movingRightFirst();
	bool movingRight = false;
	bool movingLeft = false;
};

#endif // !__PUPPLE_PATROL_STATE_H__