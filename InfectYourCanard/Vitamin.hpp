//
//  Vitamin.hpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 12/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#ifndef Vitamin_hpp
#define Vitamin_hpp

#include <stdio.h>
#include "FoodStuff.h"

class Vitamin : public FoodStuff {
    
public:
    Vitamin() {
        _id = 0;
        _flatRatioWeight    = rand() % 5 + 10.0;
        _percentRatioWeight = (rand() % 3) / 100.0 + 1.08;
        _maximum    = rand() % 500 + 3300.0;
        _minimum    = rand() % 10 + 5;
        _ratioOverTime      = 1.0077; // 1.008
        
        _icon = IMG_Load("./resources/image/CursorVitamin.png");
    }
    
    ~Vitamin() {
        _icon = nullptr;
    }
    FoodStuff* vitamin() {
        return this;
    }
    
    FoodStuff* wheat();
};

#endif /* Vitamin_hpp */
