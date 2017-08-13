//
//  LMouse.cpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 10/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#include "LMouse.hpp"

void LMouse::setCursor() {
    _cursor = SDL_CreateColorCursor(_foodstuff->getIcon(), 0, 0);
    SDL_SetCursor(_cursor);
}

void LMouse::wheat() {
    if (_foodstuff != NULL) {
        FoodStuff* wheat = _foodstuff->wheat();
        if (wheat != NULL) {
            //delete _foodstuff;
            _foodstuff = wheat;
        }
        setCursor();
    }
}

void LMouse::vitamin() {
    if (_foodstuff != NULL) {
        FoodStuff* vitamin = _foodstuff->vitamin();
        if (vitamin != NULL) {
            //delete _foodstuff;
            _foodstuff = vitamin;
        }
        setCursor();
    }
}
