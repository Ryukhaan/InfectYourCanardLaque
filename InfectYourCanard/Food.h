//
//  Food.h
//  InfectYourCanard
//
//  Created by Remi DECELLE on 19/07/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#ifndef Food_h
#define Food_h

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
#include "LTexture.h"

class Food {

protected:
    float   _flatRatioWeight;
    float   _percentRatioWeight;
    float   _maximum, _minimum;
    float   _ratioOverTime;

private:
    LTexture _texture;
    SDL_Rect _position;
    
public:
    Food() {};
    ~Food() {};

    
    // Getters
    float getPercentRatioWeight() const {
        return _percentRatioWeight;
    }
    float getFlatRatioWeight() const {
        return _flatRatioWeight;
    }
    float getMaximumWeight() const {
        return _maximum;
    }
    float getMinimumWeight() const {
        return _minimum;
    }
    float getRatioOverTime() const {
        return _ratioOverTime;
    }
    LTexture getTexture() {
        return _texture;
    }
    SDL_Rect getPosition() {
        return _position;
    }
};
#endif /* Food_h */
