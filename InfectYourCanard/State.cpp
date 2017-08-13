//
//  State.cpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 12/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#include "State.hpp"
#include "FattyState.hpp"

void State::setOrientation(int i){
    switch (i) {
        case 0: _orientation = DOWN;     break;
        case 1: _orientation = LEFT;     break;
        case 2: _orientation = RIGHT;    break;
        case 3: _orientation = UP;       break;
        default: break;
    }
}

State* State::gulp(FoodStuff *feed) {
    _weight *= feed->getPercentRatioWeight();
    _weight += feed->getFlatRatioWeight();
    _maximum_weight = feed->getMaximumWeight();
    _minimum_weight = feed->getMinimumWeight();
    _ratio_weight = feed->getRatioOverTime();
    return new FattyState(this);
}
