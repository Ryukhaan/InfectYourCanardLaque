//
//  Wheat.cpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 12/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#include "Wheat.hpp"
#include "Vitamin.hpp"

FoodStuff* Wheat::vitamin() {
    return new Vitamin();
}
