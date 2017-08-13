//
//  Vitamin.cpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 12/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#include "Vitamin.hpp"
#include "Wheat.hpp"

FoodStuff* Vitamin::wheat() {
    return new Wheat();
}
