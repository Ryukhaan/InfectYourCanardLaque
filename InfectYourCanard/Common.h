//
//  Common.h
//  InfectYourCanard
//
//  Created by Remi DECELLE on 19/07/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//



#ifndef Common_h
#define Common_h

#include <stdio.h>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>

#define MAP_WIDTH 800
#define MAP_HEIGHT 608

#define NUMBER_HEIGHT_TILES 38
#define NUMBER_WIDTH_TILES 50

#define AREA_WIDTH 40
#define AREA_HEIGHT 30

#define TILE_WIDTH 16
#define TILE_HEIGHT 16

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 608

#define NORMAL_SPEED 1
#define RUNNING_SPEED 2
#define STOPPED 0

#define STRESS_THRESHHOLD 45

#define DISTANCE_FOR_INFECT 14
#define DISTANCE_HEALTHY_VISION 42
#define DISTANCE_FATTY_VISION 48
#define DISTANCE_HEALTHY_DETECTION 16

const std::vector<int> impassable = {0, 1, 4, 5, 7, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 22, 23, 25, 27};

typedef enum {
    DOWN, LEFT, RIGHT, UP
} Orientation ;
#endif /* Common_h */
