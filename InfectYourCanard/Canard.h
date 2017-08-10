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
#include "Common.h"
#include "Food.h"
#include "LTexture.h"

typedef enum {
    FATTY, HEALTHY, STRESSED, DEAD
} State;

class Canard {
    
private:
    //bool _initialized;
    
    float _weight;
    float _ratio_weight;
    float _maximum_weight, _minimum_weight;
    int _speed;
    bool _movable;
    Orientation _orientation;
    State _state;
    int _stress;
    SDL_Rect _collider;
    LTexture* _texture;
    
    
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
    
    bool gulpDown(const Food &food);
    void putOnWeight();
    void randomWalk(bool locked);
    void stepForward(Uint32 timestep);
    void initialisePosition(const std::vector<SDL_Rect> obstacles);
    SDL_Rect checkMovable(const std::vector<SDL_Rect> obstacles);
    bool checkCollision(SDL_Rect obstacle);
    
    // Setters
    void setWeight(float weight) {
        _weight = weight;
    }
    void setRatio(float ratio) {
        _ratio_weight = ratio;
    }
    void setMaximumWeight(float maximum) {
        _maximum_weight = maximum;
    }
    void setMinimumWeight(float minimum) {
        _minimum_weight = minimum;
    }
    void setSpeed(int speed) {
        speed < 0 ? _speed = NORMAL_SPEED : _speed = speed;
    }
    void setMovable(bool movable) {
        _movable = movable;
    }
    void setOrientation(Orientation orientation) {
        _orientation = orientation;
    }
    void setOrientation(int orientation);
    void setTexture(const std::string path, SDL_Renderer *renderer);
    void setState(State state) {
        _state = state;
    }
    void setStress(int stress) {
        _stress = stress;
    }
    void setTexture(LTexture* texture) {
        _texture = texture;
    }
    
    // Getters
    float getWeight() {
        return _weight;
    }
    float getRatio() {
        return _ratio_weight;
    }
    float getMaximum() {
        return _maximum_weight;
    }
    float getMinimum() {
        return _minimum_weight;
    }
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
    State getState() {
        return _state;
    }
    int getStress() {
        return _stress;
    }
    Orientation getOrientation() {
        return _orientation;
    }
};

#endif /* Canard_h */
