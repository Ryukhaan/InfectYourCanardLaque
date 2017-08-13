//
//  FattyState.cpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 12/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#include "FattyState.hpp"
#include "HealthyState.hpp"
#include "DeadState.hpp"
#include "StressedState.hpp"

void FattyState::randomWalk(bool locked) {
    if (not locked and rand()%100 > 94)
        setOrientation(rand()%4);
}

void FattyState::increaseWeight() {
    _weight *= _ratio_weight;
}

State* FattyState::beDead() {
    return new DeadState(this);
}

State* FattyState::beHealthy() {
    return new HealthyState(this);
}

State* FattyState::beStressed() {
    return new StressState(this);
}
