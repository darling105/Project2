#ifndef __CREEP_ATTACK_STATE_H__
#define __CREEP_ATTACK_STATE_H__

#include "StateMachine/State.h"


class CreepAttackState : public State {
public:
    void enterState(Entity* owner) override;
    std::string updateState() override;
    void exitState() override;
};

#endif // __CREEP_ATTACK_STATE_H__