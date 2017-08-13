//
//  Wheat.hpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 12/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#ifndef Wheat_hpp
#define Wheat_hpp

#include <stdio.h>
#include "FoodStuff.h"

class Wheat : public FoodStuff {
public:
    Wheat() {
        _id = 1;
        _flatRatioWeight    = rand() % 5 + 15.0;
        _percentRatioWeight = 1.0;
        _maximum    = rand() % 750 + 2500.0;
        _minimum    = rand() % 10 + 15;
        _ratioOverTime      = 1.0038; // 1.003
        
        _icon = IMG_Load("./resources/image/CursorWheat.png");
    }
    ~Wheat() {
        _icon = nullptr;
    };
    
    FoodStuff* wheat() {
        return this;
    }
    FoodStuff* vitamin();
};
#endif /* Wheat_hpp */
