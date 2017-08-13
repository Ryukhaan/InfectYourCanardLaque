//
//  StressedState.hpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 12/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#ifndef StressedState_hpp
#define StressedState_hpp

#include <stdio.h>
#include "State.hpp"

class StressState : public State {
private:
    int _stressed;
    
public:
    StressState()
    : State(1)
    , _stressed(100)
    {};
    StressState(State* state)
    : State(state, 1)
    , _stressed(100)
    {};
    
    State* beStressed() {
        return this;
    };
    State* beFatty();
    State* beDead();
    State* beHealthy();
    
    void increaseWeight();
    void randomWalk(bool locked);
    
    // Getters
    int getStress() {
        return _stressed;
    }
    //State* gulp(FoodStuff* feed);
};
#endif /* StressedState_hpp */
