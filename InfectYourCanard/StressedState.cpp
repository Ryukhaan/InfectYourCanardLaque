//
//  StressedState.cpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 12/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#include "HealthyState.hpp"
#include "DeadState.hpp"
#include "FattyState.hpp"
#include "StressedState.hpp"

void StressState::randomWalk(bool locked) {
    if (locked) {
        switch (_orientation) {
            case UP:    _orientation = DOWN;    break;
            case DOWN:  _orientation = UP;      break;
            case LEFT:  _orientation = RIGHT;   break;
            case RIGHT: _orientation = LEFT;    break;
            default: break;
        }
    }
}

void StressState::increaseWeight() {
    _weight /= (_ratio_weight * 1.04); // * 1.04
    _stressed -= 3;
}


State* StressState::beDead() {
    return new DeadState(this);
}

State* StressState::beHealthy() {
    return new HealthyState(this);
}

State* StressState::beFatty() {
    return new FattyState(this);
}
