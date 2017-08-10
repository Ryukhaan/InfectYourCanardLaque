//
//  Model.h
//  InfectYourCanard
//
//  Created by Remi DECELLE on 19/07/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#ifndef Model_h
#define Model_h

#include <vector>
#include "Food.h"
#include "Canard.h"
#include "Map.h"
#include "Common.h"
//#include <SDL2/SDL.h>
//#include <SDL2_image/SDL_image.h>

class Model {
private:
    std::vector<Canard *> _ducks;
    int _numberOfDucks;
    Map* _map;
    std::vector<Food *> _foods;
    std::vector<SDL_Rect> _obstacles;
    int _score;
    LTexture* DeadTexture;
    LTexture* FattyTexture;
    LTexture* HealthyTexture;
    LTexture* StressedTexture;
    
public:
    Model(SDL_Renderer* render) {
        DeadTexture = new LTexture("resources/image/Dead.png", render);
        FattyTexture = new LTexture("resources/image/Contamine.png", render);
        HealthyTexture = new LTexture("resources/image/Canard.png", render);
        StressedTexture = new LTexture("resources/image/Stressed.png", render);
    }
    
    
    void initialiseDucks();
    void initialiseObstacles();
    void update(SDL_Renderer* render, int turnTime, SDL_Rect mouseRect);
    void render(SDL_Renderer* render, int turn);
    
    static bool sortByState (Canard* c1, Canard* c2) {
        return c1->getState() > c2->getState();
    }
    void sortDucksDead() {
        std::sort(_ducks.begin(), _ducks.end(), sortByState);
    }
    
    std::vector<Canard *> getCanards() {
        return _ducks;
    }
    
    void setDucks(const std::vector<Canard *> ducks) {
        _ducks = ducks;
    }
    
    Map* getMap() {
        return _map;
    }
    
    int getNumberOfDucks() {
        return _numberOfDucks;
    }
    
    std::vector<SDL_Rect> getObstacles() {
        return _obstacles;
    }
    
    void setObstacles(std::vector<SDL_Rect> obstacles) {
        _obstacles = obstacles;
    }
    
    void setMap(Map* map) {
        _map = map;
    }
    
    void setMap(const std::string path, SDL_Renderer *renderer) {
        _map->setTexture(path, renderer);
    }
    void makeMap(const std::string path, SDL_Renderer *renderer) {
        _map->makeTexture(path, renderer);
    }
    
    void setNumberOfDucks(int num) {
        _numberOfDucks = num;
    }
    
    void pushDuck(Canard *canard) {
        _ducks.push_back(canard);
    }
    
    void pushFood(Food *food) {
        _foods.push_back(food);
    }
    
    long sizeFood() {
        return _foods.size();
    }
    
    void eraseDuck(Canard *canard) {
        _ducks.erase(std::remove(_ducks.begin(), _ducks.end(), canard), _ducks.end());
    }
    
    void addScore(float score) {
        _score += score;
    }
    
    int getScore() {
        return _score;
    }
    
    void eraseFood(Food *food) {
        _foods.erase(std::remove(_foods.begin(), _foods.end(), food), _foods.end());
    }
    
    void generativeMap() {
        _map->generativeMapField();
    }
    
};

#endif /* Model_hpp */
