#ifndef __CHARACTER_JUMP_STATE_H__
#define __CHARACTER_JUMP_STATE_H__

#include "State.h"
#include "Map/GameMap.h"
class CharacterJumpState : public State
{
public:

	void enterState(Entity* owner) override;
	std::string updateState() override;
	void exitState() override;
	GameMap* _map;
	//CharacterJumpState() : isJumping(false) {};
private:
	//bool isJumping;
	//void jump();
};

#endif // !__CHARACTER_JUMP_STATE_H__
