#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

#include "cocos2d.h"
#include "Entity/Entity.h"
#include "State.h"
USING_NS_CC;

class StateMachine : public Node
{
public:
	//static const int AnimationTag = 100;
	//static const int EnemyAnimationTag = 10;
public:
	static StateMachine* create(Entity* entity);

	virtual bool init(Entity* entity);
	virtual void addState(std::string stateName, State* state);
	void setCurrentState(std::string _curentState);
protected:
	Entity* _entityTarget;
	std::map<std::string, State*> _states;

	std::string _currentState;
protected:
	void update(float dt);
	void onEnter() override;
};

#endif // !__STATE_MACHINE_H__
