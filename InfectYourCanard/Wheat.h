//
//  Wheat.h
//  InfectYourCanard
//
//  Created by Remi DECELLE on 28/07/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#ifndef Wheat_h
#define Wheat_h

#include "Food.h"

class Wheat : public Food {
    
public:
    Wheat() {
        _flatRatioWeight    = rand() % 5 + 15.0;
        _percentRatioWeight = 1.0;
        _maximum    = rand() % 750 + 2500.0;
        _minimum    = rand() % 10 + 15;
        _ratioOverTime      = 1.0038; // 1.003
    }
    ~Wheat() {};
};
#endif /* Wheat_h */
