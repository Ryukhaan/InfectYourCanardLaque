//
//  Map.cpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 19/07/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#include "Map.h"

Map::Map(int line, int column)
    : _timer(0)
{
    initialiseGraph();
}

// Actions
SDL_Surface* Map::createFromSurface(const std::string path) {
    SDL_Surface *surface;
    SDL_Surface *image = IMG_Load( path.c_str() );
    surface = SDL_CreateRGBSurface(0, NUMBER_WIDTH_TILES*TILE_WIDTH, NUMBER_HEIGHT_TILES*TILE_HEIGHT, 32, 0, 0, 0, 0);
    int num_vertice = 0;
    for (Vertice edge : _graph._edges) {
        int currentIndice = edge.indice;
        int i = num_vertice / AREA_HEIGHT;
        int j = num_vertice % AREA_HEIGHT;
        int positionX = (currentIndice % 10) * TILE_WIDTH;
        int positionY = (currentIndice / 10) * TILE_HEIGHT;
        SDL_Rect source = {positionX, positionY, TILE_WIDTH, TILE_HEIGHT};
        int ecranX = i*TILE_WIDTH;
        int ecranY = j*TILE_HEIGHT;
        SDL_Rect destination = {ecranX, ecranY, TILE_WIDTH, TILE_HEIGHT};
        SDL_BlitSurface(image, &source, surface, &destination);
        num_vertice++;
    }
    for(int line=0; line<NUMBER_WIDTH_TILES; line++) {
        for (int column=0; column<NUMBER_HEIGHT_TILES-AREA_HEIGHT; column++) {
            int indice = 18;
            // Top left
            if (line==0 && column==0) indice = 10;
            // Top right
            else if (line==NUMBER_WIDTH_TILES-1 && column == 0) indice = 12;
            // Bottom left
            else if (line==0 && column == NUMBER_HEIGHT_TILES-AREA_HEIGHT-1) indice = 11;
            // Bottom right
            else if(line==NUMBER_WIDTH_TILES-1 && column == NUMBER_HEIGHT_TILES-AREA_HEIGHT-1) indice = 13;
            // Left
            else if (line == 0) indice = 17;
            // Right
            else if (line== NUMBER_WIDTH_TILES-1) indice = 15;
            // Top
            else if (column == 0) indice = 14;
            // Bottom
            else if (column==NUMBER_HEIGHT_TILES-AREA_HEIGHT-1) indice = 16;

            int positionX = (indice % 10) * TILE_WIDTH;
            int positionY = (indice / 10) * TILE_HEIGHT;
            SDL_Rect source = {positionX, positionY, TILE_WIDTH, TILE_HEIGHT};
            int ecranX = line*TILE_WIDTH;
            int ecranY = (column+AREA_HEIGHT)*TILE_HEIGHT;
            SDL_Rect destination = {ecranX, ecranY, TILE_WIDTH, TILE_HEIGHT};
            SDL_BlitSurface(image, &source, surface, &destination);
        }
    }
    SDL_FreeSurface(image);
    return surface;
}

void Map::makeTexture(const std::string path, SDL_Renderer* renderer) {
    _texture.setHeight(NUMBER_HEIGHT_TILES * TILE_HEIGHT);
    _texture.setWidth(NUMBER_WIDTH_TILES * TILE_WIDTH);
    SDL_Surface* surface = createFromSurface(path);
    _texture.createFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void Map::render(SDL_Renderer *gRenderer) {
    _texture.render(gRenderer, NULL, NULL, NULL);
}

void Map::generativeMapField() {
    // Create GRASS and TREES
    
    std::vector<int> table = _graph.convertGraphToTable();
    for (int i=0 ; i< table.size(); i++) {
        rand()%12 == 0 ? table[i] = 1 : table[i] = 3;
    }

    // Creates RIVER path : LEFT -> RIGHT
    for(int num=0; num<2; num++) {
        //srand (time(NULL));
        int x = 0;
        int y = rand() %(AREA_HEIGHT-16) + 8;
        Orientation forward = LEFT;
        while(x < AREA_WIDTH) {
            int index = x * AREA_HEIGHT + y;
            table[index] = 4;
            
            Orientation lastOrientation = forward;
            // If the last orientation wasn't right, then increase change for a right move
            if (lastOrientation != RIGHT) {
                int number = rand()%4;
                if (number == 0) forward = UP;
                else if (number == 1) forward = DOWN;
                else forward = RIGHT;
            }
            // Else choose a random orientation
            else
                forward = randomDirection(rand()%4);

            // Move forward accordingly the orientation
            switch (forward) {
                case RIGHT: x++; break;
                case UP:    y--; break;
                case DOWN:  y++; break;
                default:         break;
            }
            // Check if OOB
            if (y < 0) y=0;
            if (y > AREA_HEIGHT-1) y=AREA_HEIGHT-1;
        }
    }

    // Creates RIVER path : UP <-> DOWN
    Orientation forward = LEFT;
    int x = rand()%(AREA_WIDTH-20) + 10;
    int y = (rand()%2) * (AREA_HEIGHT-1);
    bool upToDown = (y==0);
    upToDown ? forward = UP : forward = DOWN;

    int index = x * AREA_HEIGHT + y;
    while(table[index] != 4) {
        table[index] = 4;
        Orientation lastOrientation = forward;
        if (lastOrientation == RIGHT) {
            int number = rand()%3;
            if (number == 1) forward = RIGHT;
            else upToDown ? forward = DOWN : forward = UP;
        }
        else if (lastOrientation == LEFT) {
            int number = rand()%3;
            if (number == 1) forward = LEFT;
            else upToDown ? forward = DOWN : forward = UP;
        }
        else {
            int number = rand()%3;
            if (number == 0) forward = LEFT;
            else if (number == 1) forward = RIGHT;
            else upToDown ? forward = DOWN : forward = UP;
        }
        switch (forward) {
            case RIGHT: x++; break;
            case LEFT:  x--; break;
            case UP:    y--; break;
            case DOWN:  y++; break;
            default:         break;
        }
        if (x < 0) x=0;
        if (x > AREA_WIDTH) y=AREA_WIDTH;
        index = x * AREA_HEIGHT + y;
    }
    //_graph.setGraphFromTable(table);
    
    // Remove small "islands"
    // TO DO
    
    // Build bridges
    // Can be upgrade ?
    for (int i=0; i<table.size(); i++) {
        std::function<int (int,int)> toward = [](int x, int y) {return x * AREA_HEIGHT + y;};
        int x = i / AREA_HEIGHT;
        int y = i % AREA_HEIGHT;
        if ((x==0) || (y==0) || (x == AREA_WIDTH-1) || (y==AREA_HEIGHT-1))
            continue;
        if (table[i] != 4)
            continue;
        int north = toward(x, y-1);
        int south = toward(x, y+1);
        int east  = toward(x+1, y);
        int west  = toward(x-1, y);
        if (table[east] == 3 && table[west] == 3 && table[south] == 4 && table[north] == 4)
            table[i] = 2;
        if (table[south] == 3 && table[north] == 3 && table[east] == 4 && table[west] == 4)
            table[i] = 2;
    }
    
    _graph.setGraphFromTable(table);
}

void Map::generativeMapSnow() {
    // Create GRASS and TREES
    std::function<int (int,int)> toward = [](int x, int y) {return x * AREA_HEIGHT + y;};
    std::vector<int> table = _graph.convertGraphToTable();
    for (int i=0 ; i< table.size(); i++) {
        int choice = rand()%15;
        if (choice == 0) table[i] = 25;
        else if (choice == 1) table[i] = 27;
        else table[i] = 26;
    }
    
    //srand (time(NULL));
    int x = rand()%(AREA_WIDTH-20) + 10;
    int y = 1;
    int horaire = 3;
    
    // Creates RIVER path : LEFT -> RIGHT
    while(y < AREA_HEIGHT-1) {
        table[toward(x-1, y)] = 4;
        table[toward(x-1, y-1)] = 4;
        table[toward(x-1, y+1)] = 4;
        
        table[toward(x, y)] = 4;
        table[toward(x, y-1)] = 4;
        table[toward(x, y+1)] = 4;
        
        table[toward(x+1, y)] = 4;
        table[toward(x+1, y-1)] = 4;
        table[toward(x+1, y+1)] = 4;
        
        int right = rand()%2;
        right == 0 ? horaire-- : horaire++;
        horaire = horaire % 8;
        switch (horaire) {
            // TOP-LEFT
            case 0: x--; y--; break;
            case 1: x--; break;
            case 2: x--; y++; break;
            case 3: y++; break;
            case 4: x++; y++; break;
            case 5: x++; break;
            case 6: x++; y--; break;
            case 7: y--; break;
            default:
                break;
        }
        if (x < 1) x = 1;
        if (x > AREA_WIDTH-1) x = AREA_WIDTH-1;
        if (y < 1) y = 1;
    }

    
    // Remove small "islands"
    // TO DO
    
    // Build bridges
    // Can be upgrade ?
    /*
     for (int i=0; i<table.size(); i++) {
        int x = i / AREA_HEIGHT;
        int y = i % AREA_HEIGHT;
        if ((x==0) || (y==0) || (x == AREA_WIDTH-1) || (y==AREA_HEIGHT-1))
            continue;
        if (table[i] != 4)
            continue;
        int north = toward(x, y-1);
        int south = toward(x, y+1);
        int east  = toward(x+1, y);
        int west  = toward(x-1, y);
        Orientation orientation = LEFT;
        if (table[east] == 26 && table[west] == 4 && table[south] == 4 && table[north] == 4)
            orientation = RIGHT;
        if (table[east] == 4 && table[west] == 26 && table[south] == 4 && table[north] == 4)
            orientation = LEFT;
        if (table[east] == 4 && table[west] == 4 && table[south] == 26 && table[north] == 4)
            orientation = DOWN;
        if (table[east] == 4 && table[west] == 4 && table[south] == 4 && table[north] == 26)
            orientation = UP;
        switch (orientation) {
            case DOWN: y++; break;
            case UP: y--; break;
            case LEFT: x--; break;
            case RIGHT: x++; break;
            default: break;
        }
        int j = x * AREA_HEIGHT + y;
        while(table[j] == 4) {
            table[j] = 2;
            switch (orientation) {
                case DOWN: y++; break;
                case UP: y--; break;
                case LEFT: x--; break;
                case RIGHT: x++; break;
                default: break;
            }
        }
    }
    */
    _graph.setGraphFromTable(table);
}

void Map::generativeMapLava() {
    std::function<int (int,int)> toward = [](int x, int y) {return x * AREA_HEIGHT + y;};
    std::vector<int> table = _graph.convertGraphToTable();
    for (int i=0 ; i< table.size(); i++) {
        table[i] = 7;
    }
    
    int limit = 1250;
    int mass = 0;
    std::vector<int> pile;
    pile.push_back(toward(AREA_WIDTH / 2, AREA_HEIGHT / 2));
    while (mass < limit) {
        while (pile.size() != 0) {
            if (mass >= limit) break;
            int index = pile.back();
            pile.pop_back();
            mass ++;
            if (table[index] == 6) continue;
            table[index] = 6;
            for (int child=0; child<2; child++) {
                int x = index / AREA_HEIGHT;
                int y = index % AREA_HEIGHT;
                Orientation children = randomDirection(rand()%4);
                switch (children) {
                    case LEFT:  x--; break;
                    case RIGHT: x++; break;
                    case UP:    y--; break;
                    case DOWN:  y++; break;
                    default:
                        break;
                }
                x = std::min(AREA_WIDTH-1,std::max(0,x));
                y = std::min(AREA_HEIGHT-1,std::max(0,y));
                pile.push_back(toward(x,y));
            }
        }
        pile.push_back(toward(rand()%AREA_WIDTH, rand()%AREA_HEIGHT));
    }
    for (int i=0 ; i< table.size(); i++) {
        if (table[i] == 6 )
            if (rand()%10==0)
                table[i] = 5;
    }
    _graph.setGraphFromTable(table);
}

// Setters
void Map::setTimer(int timer) {
    _timer = timer;
}

void Map::setTile(int x, int y, int value) {
    //_table[x][y] = value;
}

void Map::setTexture(const std::string path, SDL_Renderer *renderer) {
    _texture.loadFromFile(path, renderer);
}
// Getters

int Map::getTimer() {
    return _timer;
}

std::vector<int> Map::getVerticesIndices() {
    std::vector<int> indices;
    for (Vertice v : _graph._edges) {
        indices.push_back(v.indice);
    }
    return indices;
}

void Map::initialiseGraph() {
    _graph.setGraphFromTable({});
}

std::vector<Vertice*> Map::groundGraph(const Graph graph, Vertice* start) {
    //Graph subGraph = *new Graph();
    std::vector<Vertice*> subGraph;
    std::vector<Vertice*> pile;
    std::vector<Vertice*> marks;
    std::vector<Vertice*> voisins = graph.neighbors(*start);
    
    subGraph.push_back(start);
    pile.push_back(start);
    marks.push_back(start);
    // Tant que la pile n'est pas vide (toujours des sommets à visiter)
    while (pile.size() != 0) {
        // Récuperer le sommet
        Vertice* sommet = pile.front();
        pile.erase(pile.begin());
        // Get neighboors
        voisins = graph.neighbors(*sommet);
        // For each neighboor
        for (Vertice* voisin : voisins) {
            if (voisin == nullptr) break;
            bool isMarked = false;
            //
            for (Vertice* mark : marks) {
                if (voisin==mark) {
                    isMarked=true;
                    break;
                }
            }
            if (!isMarked && voisin->indice != 4) {
                pile.push_back(voisin);
                marks.push_back(voisin);
                subGraph.push_back(voisin);
            }
        }
    }
    return subGraph;
}
