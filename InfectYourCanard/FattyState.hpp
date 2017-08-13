//
//  FattyState.hpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 12/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#ifndef FattyState_hpp
#define FattyState_hpp

#include <stdio.h>
#include "State.hpp"

class FattyState : public State {
private:
    int _stressed;
public:
    FattyState()
    : State(2)
    {};
    FattyState(State* state)
    : State(state, 2)
    {};
    
    ~FattyState() {};
    
    State* beStressed();
    State* beFatty() {
        return this;
    };
    State* beDead();
    State* beHealthy();
    
    void increaseWeight();
    void randomWalk(bool locked);
};
#endif /* FattyState_hpp */
