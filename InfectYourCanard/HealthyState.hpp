//
//  HealthyState.hpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 12/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#ifndef HealthyState_hpp
#define HealthyState_hpp

#include <stdio.h>
#include "State.hpp"

class HealthyState : public State {
public:
    HealthyState()
    : State(0)
    {};
    HealthyState(State* state)
    : State(state, 0)
    {};
    
    State* beStressed();
    State* beFatty();
    State* beDead();
    State* beHealthy() {
        return this;
    }
    void increaseWeight();
    void randomWalk(bool locked);
    //State* gulp(FoodStuff* feed);
};
#endif /* HealthyState_hpp */
