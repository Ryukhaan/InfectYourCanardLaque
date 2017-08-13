//
//  FoodStuff.h
//  InfectYourCanard
//
//  Created by Remi DECELLE on 12/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#ifndef FoodStuff_h
#define FoodStuff_h

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Common.h"

class FoodStuff {
protected:
    float   _flatRatioWeight;
    float   _percentRatioWeight;
    float   _maximum, _minimum;
    float   _ratioOverTime;
    int     _id;
    SDL_Surface* _icon;
    
public:
    FoodStuff() {};
    virtual ~FoodStuff() {};
    
    virtual FoodStuff* vitamin() = 0;
    virtual FoodStuff* wheat() = 0;
    
    int const getID() {
        return _id;
    }
    
    float getPercentRatioWeight() {
        return _percentRatioWeight;
    }
    float getFlatRatioWeight() {
        return _flatRatioWeight;
    }
    float getMaximumWeight() {
        return _maximum;
    }
    float getMinimumWeight() {
        return _minimum;
    }
    float getRatioOverTime() {
        return _ratioOverTime;
    }
    SDL_Surface* const getIcon() {
        return _icon;
    }
};
#endif /* FoodStuff_h */
