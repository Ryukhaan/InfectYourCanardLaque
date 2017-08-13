//
//  State.hpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 12/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#ifndef State_hpp
#define State_hpp

#include <stdio.h>
#include "Common.h"
#include "FoodStuff.h"

class State {
protected:
    float _weight;
    float _ratio_weight;
    float _maximum_weight, _minimum_weight;
    Orientation _orientation;
    int _id;

public:
    State(int i)
    : _id(i)
    {
        _weight = rand() % 10 + 45.0;
        _ratio_weight = 1.001;
        _maximum_weight = rand() % 700 + 2800;
        _minimum_weight = rand() % 10 + 25;
        setOrientation(rand()%4);
    };
    
    State(State* state, int i)
    : _id(i)
    {
        _weight = state->getWeight();
        _ratio_weight = state->getRatio();
        _maximum_weight = state->getMaximum();
        _minimum_weight = state->getMinimum();
        _orientation = state->getOrientation();
    };
    
    virtual ~State() {};
    
    virtual State* beStressed() = 0;
    virtual State* beFatty() = 0;
    virtual State* beHealthy() = 0;
    virtual State* beDead() = 0;
    virtual void increaseWeight() = 0;
    virtual void randomWalk(bool locked) = 0;
    
    virtual State* gulp(FoodStuff* feed);
    void setOrientation(int i);
    
    // Setters
    void setWeight(float weight) {
        _weight = weight;
    }
    void setRatio(float ratio) {
        _ratio_weight = ratio;
    }
    void setMaximumWeight(float maximum) {
        _maximum_weight = maximum;
    }
    void setMinimumWeight(float minimum) {
        _minimum_weight = minimum;
    }
    void setOrientation(Orientation orientation) {
        _orientation = orientation;
    }
    
    // Getters
    float getWeight() {
        return _weight;
    }
    float getRatio() {
        return _ratio_weight;
    }
    float getMaximum() {
        return _maximum_weight;
    }
    float getMinimum() {
        return _minimum_weight;
    }
    Orientation getOrientation() {
        return _orientation;
    }

    int const getID() {
        return _id;
    }
};
#endif /* State_hpp */
