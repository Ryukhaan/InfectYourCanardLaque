//
//  Vitamin.h
//  InfectYourCanard
//
//  Created by Remi DECELLE on 28/07/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#ifndef Vitamin_h
#define Vitamin_h

#include "Food.h"

class Vitamin : public Food {
    
public:
    Vitamin() {
        _flatRatioWeight    = rand() % 5 + 30.0;
        _percentRatioWeight = (rand() % 10) / 10.0 + 4.5;
        _maximum    = rand() % 500 + 3250.0;
        _minimum    = rand() % 10 + 5;
        _ratioOverTime      = 1.0076; // 1.008
    }
    ~Vitamin() {};
};
#endif /* Vitamin_h */
