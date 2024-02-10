#ifndef __CHARACTER_RUN_STATE_H__
#define __CHARACTER_RUN_STATE_H__

#include "StateMachine/State.h"
#include "MapUtilities/GameMap.h"

class CharacterRunState : public State
{
public:
	void enterState(Entity* owner) override;
	std::string updateState() override;
	void exitState() override;
	GameMap* _map;
};

#endif // !__CHARACTER_RUN_STATE_H__
