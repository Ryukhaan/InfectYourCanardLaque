//
//  LMouse.hpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 10/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#ifndef LMouse_hpp
#define LMouse_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "FoodStuff.h"
#include "Common.h"

typedef enum {
   WHEAT, VITAMIN
} Status ;

class LMouse {
public:
    LMouse()
    : _radius(DEFAULT_RADIUS)
    , _foodstuff(nullptr)
    , _buttonDown(false)
    ,_cursor(nullptr)
    {};
    
    ~LMouse();
    
    void setPosition(int x, int y) {
        int centering = _radius / 2;
        _x = x + centering;
        _y = y + centering;
    }
    
    float const realRadius() {
       float centering = _radius / 2;
       return sqrtf(2.0f) * centering;
    }
    
    // Getters
    int getX() const{
        return _x;
    }
    int getY() const {
        return _y;
    }
    float getRadius() const {
        return _radius;
    }
    SDL_Cursor* getCursor() const{
        return _cursor;
    }
    bool const isPressed()  {
        return _buttonDown;
    }
    
    FoodStuff* getFeed() const {
        return _foodstuff;
    }
    
    // Setters
    void setX(const int x) {
        _x = x;
    }
    void setY(const int y) {
        _y = y;
    }
    void setRadius(const float radius) {
        _radius = radius;
    }
    
    void setCursor();

    void switchOnButton() {
        _buttonDown = true;
    }
    void switchOffButton() {
        _buttonDown = false;
    }
    
    void setFoodStuff(FoodStuff* foodstuff) {
        _foodstuff = foodstuff;
        setCursor();
    }
    void wheat();
    void vitamin();
    
private:
    int _x, _y;
    float _radius;
    SDL_Cursor* _cursor;
    bool _buttonDown;
    FoodStuff* _foodstuff;
};
#endif /* LMouse_hpp */
