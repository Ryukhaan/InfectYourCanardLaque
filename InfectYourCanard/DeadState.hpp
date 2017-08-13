//
//  DeadState.hpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 12/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#ifndef DeadState_hpp
#define DeadState_hpp

#include <stdio.h>
#include "State.hpp"

class DeadState : public State {
public:
    DeadState()
    : State(-1)
    {};
    DeadState(State* state)
    : State(state, -1)
    {};
    
    ~DeadState() {};
    
    State* beStressed();
    State* beFatty();
    State* beHealthy();
    State* beDead() {
        return this;
    };
    
    void increaseWeight();
    void randomWalk(bool locked);
};
#endif /* DeadState_hpp */
