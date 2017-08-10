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
#include "LTexture.h"

typedef enum {
   WHEAT, VITAMIN
} Status ;

class LMouse {
public:
    static const int DEFAULT_RADIUS = 48;
    
    LMouse()
    : _radius(0)
    , _status(VITAMIN)
    {
        _buttonDown = false;
        _cursor = nullptr;
    };
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
    Status getStatus() {
        return _status;
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
    void setCursor(SDL_Surface* surface) {
        _cursor = SDL_CreateColorCursor(surface, 0, 0);
        SDL_SetCursor(_cursor);
    }
    void switchOnButton() {
        _buttonDown = true;
    }
    void switchOffButton() {
        _buttonDown = false;
    }
    void switchStatus() {
        switch (_status) {
            case VITAMIN: _status = WHEAT; break;
            case WHEAT: _status = VITAMIN; break;
            default: break;
        }
    }
private:
    int _x, _y;
    float _radius;
    SDL_Cursor* _cursor;
    bool _buttonDown;
    Status _status;
};
#endif /* LMouse_hpp */
