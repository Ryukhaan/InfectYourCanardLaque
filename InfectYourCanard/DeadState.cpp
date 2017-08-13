//
//  DeadState.cpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 12/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#include "DeadState.hpp"
#include "HealthyState.hpp"
#include "FattyState.hpp"
#include "StressedState.hpp"

void DeadState::randomWalk(bool locked) {
    return;
}

void DeadState::increaseWeight() {
    return;
}

State* DeadState::beFatty() {
    return new FattyState(this);
}

State* DeadState::beHealthy() {
    return new HealthyState(this);
}

State* DeadState::beStressed() {
    return new StressState(this);
}
