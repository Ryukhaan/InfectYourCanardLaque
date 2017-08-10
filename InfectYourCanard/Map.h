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
    std::vector<std::vector<int>> _table;
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
    void pushNewLine();
    void pushTile(int line, int value);
    void generativeMapField();
    
    // Getters
    int getTimer();
    int getTile(int x, int y);
    std::vector<std::vector<int>> getTable();
    std::vector<std::vector<int>> copyTable();
    
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
    
    Graph createGraphFromMap();
    Graph groundGraph(Graph g, Vertice start);
    Graph waterGraph(Graph g, Vertice start);
    void buildBridge(Graph g);
};
#endif /* Map_hpp */
