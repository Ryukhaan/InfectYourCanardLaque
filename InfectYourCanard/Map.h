//
//  Map.h
//  InfectYourCanard
//
//  Created by Remi DECELLE on 19/07/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#ifndef Map_h
#define Map_h

#include <vector>
#include "Common.h"
#include "LTexture.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Graph.hpp"

class Map {
private:
    int _timer;
    Graph _graph;
    LTexture _texture;
    
public:
    Map() {}
    Map(int line, int column);
    ~Map() {}
    void initialise(int line, int column);
    
    // Actions
    SDL_Surface* createFromSurface(const std::string path);
    void makeTexture(const std::string path, SDL_Renderer* renderer);
    void render(SDL_Renderer* gRenderer);
    void generativeMapField();
    void generativeMapSnow();
    void generativeMapLava();
    // Getters
    int getTimer();
    std::vector<int> getVerticesIndices();
    
    // Setters
    void setTexture(const std::string path, SDL_Renderer *renderer);
    void setTimer(int timer);
    void setTile(int x, int y, int value);
    
    // Others
    Orientation randomDirection(int r) {
        switch (r) {
            case 0: return LEFT;
            case 1: return UP;
            case 2: return DOWN;
            case 3: return RIGHT;
            default: return LEFT;
        }
    }
    
    void initialiseGraph();
    std::vector<Vertice*> groundGraph(const Graph g, Vertice* start);
};
#endif /* Map_hpp */
