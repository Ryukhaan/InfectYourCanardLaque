//
//  Canard.h
//  InfectYourCanard
//
//  Created by Remi DECELLE on 18/07/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#pragma once

#ifndef Canard_h
#define Canard_h

#include <stdio.h>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "LMouse.hpp"
#include "LTexture.h"
#include "LTile.h"
#include "State.hpp"
#include "HealthyState.hpp"
#include "FattyState.hpp"
#include "DeadState.hpp"
#include "StressedState.hpp"

/*
typedef enum {
    FATTY, HEALTHY, STRESSED, DEAD
} State;
*/

class Canard {
    friend class DGrid;
    //class Status* _status;
    
private:
    int _speed;
    bool _movable;
    State* _state;

    SDL_Rect _collider;
    LTexture* _texture;
    Canard* _next;
    Canard* _prev;
    
public:
    // Constructor and Deconstrutor
    Canard();
    Canard(LTexture* texture);
    ~Canard();
    void initialise();
    void deletion();
    
    // Actions
    void render(SDL_Renderer *renderer, Uint8 turn);
    void update(Uint32 timestep, const std::vector<SDL_Rect> obstacles, bool locked);
    void handle(SDL_Event* event);
    
    float distanceBetween(Canard const &canard);
    bool sameX(Canard const &canard) {
        return canard._collider.x >= _collider.x
            && canard._collider.x <= _collider.x + TILE_HEIGHT;
    }
    bool sameY(Canard const &canard) {
        return canard._collider.y >= _collider.y
            && canard._collider.y <= _collider.y + TILE_WIDTH;
    }
    float affineYplusX(Canard const &canard) {
        return - canard._collider.y + _collider.y - canard._collider.x + _collider.x;
    }
    float affineYminusX(Canard const &canard) {
        return - canard._collider.y + _collider.y + canard._collider.x - _collider.x;
    }
    
    bool gulpDown(FoodStuff* feed);
    void putOnWeight();
    void randomWalk(bool locked);
    void stepForward(Uint32 timestep);
    void initialisePosition(const std::vector<SDL_Rect> obstacles);
    SDL_Rect checkMovable(const std::vector<SDL_Rect> obstacles);
    bool checkCollision(SDL_Rect obstacle);
    
    // Setters
    void setSpeed(int speed) {
        speed < 0 ? _speed = NORMAL_SPEED : _speed = speed;
    }
    void setMovable(bool movable) {
        _movable = movable;
    }

    void setTexture(const std::string path, SDL_Renderer *renderer);
    void setState(State* state) {
        _state = state;
    }
    
    void setTexture(LTexture* texture) {
        _texture = texture;
    }
    void setX(int x) {
        _collider.x = x;
    }
    void setY(int y) {
        _collider.y = y;
    }
    void setNext(Canard* next) {
        _next = next;
    }
    void setPrev(Canard* prev) {
        _prev = prev;
    }
    void setRatio(float ratio) {
        _state->setRatio(ratio);
    }
    
    // Getters
    int getSpeed() {
        return _speed;
    }
    bool isMovable() {
        return _movable;
    }
    int getX() {
        return _collider.x;
    }
    int getY() {
        return _collider.y;
    }
    SDL_Rect getCollider() {
        return _collider;
    }
    LTexture* getTexture() {
        return _texture;
    }
    State* getState() {
        return _state;
    }
    
    Canard* getNext() {
        return _next;
    }
    Canard* getPrev() {
        return _prev;
    }
    float getRatio() {
        return _state->getRatio();
    }
    // State actions
    void fatty();
    void healthy();
    void stressed();
    void dead();
};

#endif /* Canard_h */
