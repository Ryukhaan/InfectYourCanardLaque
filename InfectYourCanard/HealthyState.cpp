//
//  HealthyState.cpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 12/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#include "HealthyState.hpp"
#include "DeadState.hpp"
#include "FattyState.hpp"
#include "StressedState.hpp"

void HealthyState::randomWalk(bool locked) {
    if (rand()%100 > 94)
        setOrientation(rand() % 4);
}

void HealthyState::increaseWeight() {
    _weight += _ratio_weight;
}


State* HealthyState::beDead() {
    return new DeadState(this);
}

State* HealthyState::beStressed() {
    return new StressState(this);
}

State* HealthyState::beFatty() {
    return new FattyState(this);
}
