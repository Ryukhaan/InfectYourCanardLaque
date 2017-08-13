//
//  Canard.cpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 19/07/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#include "Canard.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>

Canard::Canard() {
    initialise();
}

Canard::Canard(LTexture* texture) {
    initialise();
    setTexture(texture);
}

Canard::~Canard() {
    deletion();
}

void Canard::initialise() {
    //Initialize the variables
    _speed = NORMAL_SPEED;
    
    // State
    _state = new HealthyState();
    
    // Collision box
    _collider.x = rand() % ((AREA_WIDTH-1) * TILE_WIDTH);
    _collider.y = rand() % ((AREA_HEIGHT-1) * TILE_HEIGHT);
    _collider.w = TILE_WIDTH;
    _collider.h = TILE_HEIGHT;
    
    // Texture
    //_texture;
}

void Canard::randomWalk(bool locked) {
    _state->randomWalk(locked);
}

void Canard::initialisePosition(const std::vector<SDL_Rect> obstacles) {
    bool doit = false;
    do {
        doit = false;
        _collider.x = rand() % ((AREA_WIDTH-1) * TILE_WIDTH);
        _collider.y = rand() % ((AREA_HEIGHT-1) * TILE_HEIGHT);
        for (SDL_Rect obstacle : obstacles) {
            if (checkCollision(obstacle)) {
                doit = true;
            }
        }
    } while(doit);
    
}

void Canard::deletion() {
};

// Actions
float Canard::distanceBetween(Canard const &canard) {
    float x_diff = (_collider.x - canard._collider.x);
    float y_diff = (_collider.y - canard._collider.y);
    return sqrtf(x_diff * x_diff + y_diff * y_diff);
}

bool Canard::gulpDown(FoodStuff* feed) {
    _state->gulp(feed);
    return true;
}

void Canard::putOnWeight() {
    _state->increaseWeight();
}

void Canard::stepForward(Uint32 timestep) {
    switch (_state->getOrientation()) {
        case DOWN   : _collider.y += _speed ; break;
        case UP     : _collider.y -= _speed ; break;
        case LEFT   : _collider.x -= _speed ; break;
        case RIGHT  : _collider.x += _speed ; break;
        default     :       break;
    }
    _collider.y = std::min(_collider.y, (AREA_HEIGHT-1)*TILE_HEIGHT);
    _collider.y = std::max(_collider.y, 0);
    SDL_assert(_collider.y <= (AREA_HEIGHT-1)*TILE_HEIGHT and _collider.y >= 0);
    
    _collider.x = std::min(_collider.x, (AREA_WIDTH-1)*TILE_WIDTH);
    _collider.x = std::max(_collider.x, 0);
    SDL_assert(_collider.x <= (AREA_WIDTH-1)*TILE_WIDTH and _collider.x >= 0);
}

void Canard::render(SDL_Renderer* renderer, Uint8 turn) {
    SDL_Rect source;
    if (_state->getID() != -1)
        source = {turn * TILE_HEIGHT, _state->getOrientation() * TILE_WIDTH, TILE_WIDTH , TILE_HEIGHT};
    else
        source = {0, 0, TILE_WIDTH, TILE_HEIGHT};
    _texture->render(renderer, &source, _collider.x, _collider.y);
}

void Canard::update(Uint32 timestep, const std::vector<SDL_Rect> obstacles, bool locked) {
    if (_state->getID() != -1) // not DEAD
    {
        randomWalk(locked);
        stepForward(timestep);
        SDL_Rect back = checkMovable(obstacles);
        if (not _movable) {
            _collider = back;
            //randomWalk(locked);
            int newOrientation = (rand() % 4);
            while (newOrientation == _state->getOrientation())
                newOrientation = rand() % 4;
            _state->setOrientation(newOrientation);
        }
        putOnWeight();
    }
}

void Canard::handle(SDL_Event *event) {
    Mix_Chunk* coincoin = Mix_LoadWAV("resources/audio/duckSound.wav");
    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_MOUSEMOTION:
                Mix_PlayChannel(1, coincoin, 0);
                break;
            default:
                break;
        }
    }
    Mix_FreeChunk(coincoin);
}

SDL_Rect Canard::checkMovable(const std::vector<SDL_Rect> obstacles) {
    SDL_Rect stepBackward;
    stepBackward.w = TILE_WIDTH;
    stepBackward.h = TILE_HEIGHT;
    stepBackward.x = _collider.x;
    stepBackward.y = _collider.y;
    _movable = true;
    switch (_state->getOrientation()) {
        case DOWN:
            if (not (_collider.y < (AREA_HEIGHT-1)*TILE_HEIGHT)) {
                _movable = false;
                stepBackward.y --;
                return stepBackward;
            }
            break;
        case LEFT:
            if (not (_collider.x > 0)) {
                _movable = false;
                stepBackward.x ++;
                return stepBackward;
            }
            break;
        case RIGHT:
            if (not (_collider.x < (AREA_WIDTH-1)*TILE_WIDTH)) {
                _movable = false;
                stepBackward.x --;
                return stepBackward;
            }
            break;
        case UP:
            if (not (_collider.y > 0))  {
                _movable = false;
                stepBackward.y ++;
                return stepBackward;
            }
            break;
        default:
            break;
    }
    for (SDL_Rect obstacle : obstacles) {
        if (checkCollision(obstacle)) {
            switch (_state->getOrientation()) {
                case DOWN:  stepBackward.y -= _speed; break;
                case UP:    stepBackward.y += _speed; break;
                case LEFT:  stepBackward.x += _speed; break;
                case RIGHT: stepBackward.x -= _speed; break;
                default: break;
            }
            _movable = false;
            return stepBackward;
        }
    }
    return stepBackward;
}

bool Canard::checkCollision(SDL_Rect obstacle) {
    int leftObstacle, rightObstacle, topObstacle, bottomObstacle;
    int leftCollider, rightCollider, topCollider, bottomCollider;
    
    // Calculate the sides of _collider
    leftCollider = _collider.x;
    rightCollider = _collider.x + _collider.w;
    topCollider = _collider.y;
    bottomCollider = _collider.y + _collider.h;
    
    // Calculate the side of rect obstacle
    leftObstacle = obstacle.x;
    rightObstacle = obstacle.x + obstacle.w;
    topObstacle = obstacle.y;
    bottomObstacle = obstacle.y + obstacle.h;
    if (rightCollider <= leftObstacle)
        return false;
    if (leftCollider >= rightObstacle)
        return false;
    if (topCollider >= bottomObstacle)
        return false;
    if (bottomCollider <= topObstacle)
        return false;
    return true;
}

// Setters
void Canard::fatty() {
    if (_state != NULL) {
        State* fatty = _state->beFatty();
        if (fatty != NULL) {
            //delete _state;
            _state = nullptr;
            _state = fatty;
        }
    }
}

void Canard::healthy() {
    if (_state != NULL) {
        State* healthy = _state->beHealthy();
        if (healthy != NULL) {
            //delete _state;
            _state = nullptr;
            _state = healthy;
        }
    }
}
void Canard::stressed() {
    if (_state != NULL) {
        State* stressed = _state->beStressed();
        if (stressed != NULL) {
            //delete _state;
            _state = nullptr;
            _state = stressed;
        }
    }
}
void Canard::dead() {
    if (_state != NULL) {
        State* dead = _state->beDead();
        if (dead != NULL) {
            //delete _state;
            _state = nullptr;
            _state = dead;
        }
    }
}
