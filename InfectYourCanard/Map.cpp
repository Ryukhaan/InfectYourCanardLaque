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
    //_texture = *new LTexture();
    //malloc(sizeof(LTexture));
    initialise(line, column);
}

void Map::initialise(int line, int column) {
    for (int i=0; i<line; i++) {
        pushNewLine();
        for (int j=0; j<column; j++) {
            pushTile(i, 0);
        }
    }
}

// Actions
SDL_Surface* Map::createFromSurface(const std::string path) {
    SDL_Surface *surface;
    SDL_Surface *image = IMG_Load( path.c_str() );
    surface = SDL_CreateRGBSurface(0, NUMBER_WIDTH_TILES*TILE_WIDTH, NUMBER_HEIGHT_TILES*TILE_HEIGHT, 32, 0, 0, 0, 0);
    for (int i=0; i<_table.size(); i++) {
        for (int j=0; j<_table[i].size(); j++) {
            int positionX = (_table[i][j] % 10) * TILE_WIDTH;
            int positionY = (_table[i][j] / 10) * TILE_HEIGHT;
            SDL_Rect source = {positionX, positionY, TILE_WIDTH, TILE_HEIGHT};
            int ecranX = i*TILE_WIDTH;
            int ecranY = j*TILE_HEIGHT;
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

void Map::pushNewLine() {
    _table.push_back(std::vector<int>());
}

void Map::pushTile(int line, int value) {
    _table[line].push_back(value);
}

void Map::generativeMapField() {
    // Create GRASS and TREES
    for (int i=0; i<AREA_WIDTH; i++) {
        for (int j=0; j<AREA_HEIGHT; j++) {
            rand()%12 == 0 ? _table[i][j] = 1 : _table[i][j] = 3;
        }
    }
    
    // Creates RIVER path : LEFT -> RIGHT
    for(int num=0; num<2; num++) {
        //srand (time(NULL));
        int x = 0;
        int y = rand() %(AREA_HEIGHT-16) + 8;
        Orientation forward = LEFT;
        while(x < AREA_WIDTH) {
            _table[x][y] = 4;
            
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
    while(_table[x][y] != 4) {
        _table[x][y] = 4;
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
    }
    
    
    // Remove small "islands"
    Graph graph = createGraphFromMap();
    std::vector<Graph> graphs = {};
    
    Vertice start = {0, 0, _table[0][0]};
    Graph subGraph = groundGraph(graph, start);
    graphs.push_back(subGraph);
    for (int i=0; i<AREA_WIDTH; i++) {
        for (int j=0; j<AREA_HEIGHT; j++) {
            if (_table[i][j] == 4) continue;
            start = {i, j, _table[i][j]};
            bool notVisited = true;
            for (Graph g : graphs) {
                if (g.has(start)) {
                    notVisited = false;
                    break;
                }
            }
            if (notVisited) {
                std::cout << "Add a graph" << std::endl;
                subGraph = groundGraph(graph, start);
                graphs.push_back(subGraph);
            }
        }
    }
    for(Graph g : graphs) {
        if (g.size() < 120) {
            for (std::pair<Vertice, std::vector<Vertice>> node : g._edges) {
                Vertice v = node.first;
                _table[v.x][v.y] = 4;
            }
        }
    }
    
    start = {0, 0, _table[0][0]};
    Graph graphForBridge = waterGraph(graph, start);
    buildBridge(graphForBridge);
    
    std::cout << graphs.size() << std::endl;
}

// Setters
void Map::setTimer(int timer) {
    _timer = timer;
}

void Map::setTile(int x, int y, int value) {
    _table[x][y] = value;
}

void Map::setTexture(const std::string path, SDL_Renderer *renderer) {
    _texture.loadFromFile(path, renderer);
}
// Getters

int Map::getTimer() {
    return _timer;
}

int Map::getTile(int x, int y) {
    return _table[x][y];
}

std::vector<std::vector<int>> Map::getTable() {
    return _table;
}

std::vector<std::vector<int>> Map::copyTable() {
    std::vector<std::vector<int>> copy;
    for (std::vector<int> line : _table) {
        copy.push_back(line);
    }
    return copy;
}

Graph Map::createGraphFromMap() {
    Graph graph;
    for (int i=0; i<AREA_WIDTH; i++) {
        for (int j=0; j<AREA_HEIGHT; j++) {
            Vertice v = {i,j,_table[i][j]};
            // Up Left Corner
            if (i==0 && j==0) {
                Vertice v1 = {i+1,j,_table[i+1][j]};
                Vertice v2 = {i,j+1,_table[i][j+1]};
                std::vector<Vertice> e = {v1, v2};
                graph.addEdge(v, e);
            }
            // Up Right Corner
            else if (i==AREA_WIDTH-1 && j==0) {
                Vertice v1 = {i-1,j,_table[i-1][j]};
                Vertice v2 = {i,j+1,_table[i][j+1]};
                std::vector<Vertice> e = {v1, v2};
                graph.addEdge(v, e);
            }
            // Down Left Corner
            else if (i==0 && j==AREA_HEIGHT-1) {
                Vertice v1 = {i+1,j,_table[i+1][j]};
                Vertice v2 = {i,j-1,_table[i][j-1]};
                std::vector<Vertice> e = {v1, v2};
                graph.addEdge(v, e);
            }
            // Down Right Corner
            else if (i==AREA_WIDTH-1 && j==AREA_HEIGHT-1) {
                Vertice v1 = {i-1,j,_table[i-1][j]};
                Vertice v2 = {i,j-1,_table[i][j-1]};
                std::vector<Vertice> e = {v1, v2};
                graph.addEdge(v, e);
            }
            // Left Border
            else if (i==0) {
                Vertice v1 = {i+1,j,_table[i+1][j]};
                Vertice v2 = {i,j+1,_table[i][j+1]};
                Vertice v3 = {i,j-1,_table[i][j-1]};
                std::vector<Vertice> e = {v1, v2, v3};
                graph.addEdge(v, e);
            }
            // Right Border
            else if (i==AREA_WIDTH-1) {
                Vertice v1 = {i-1,j,_table[i-1][j]};
                Vertice v2 = {i,j+1,_table[i][j+1]};
                Vertice v3 = {i,j-1,_table[i][j-1]};
                std::vector<Vertice> e = {v1, v2, v3};
                graph.addEdge(v, e);
            }
            // Up Border
            else if (j==0) {
                Vertice v1 = {i+1,j,_table[i+1][j]};
                Vertice v2 = {i-1,j,_table[i-1][j]};
                Vertice v3 = {i,j+1,_table[i][j+1]};
                std::vector<Vertice> e = {v1, v2, v3};
                graph.addEdge(v, e);
            }
            // Down Border
            else if (j==AREA_HEIGHT-1) {
                Vertice v1 = {i+1,j,_table[i+1][j]};
                Vertice v2 = {i-1,j,_table[i-1][j]};
                Vertice v3 = {i,j-1,_table[i][j-1]};
                std::vector<Vertice> e = {v1, v2, v3};
                graph.addEdge(v, e);
            }
            // Normal case
            else {
                Vertice v1 = {i+1,j,_table[i+1][j]};
                Vertice v2 = {i-1,j,_table[i-1][j]};
                Vertice v3 = {i,j+1,_table[i][j+1]};
                Vertice v4 = {i,j-1,_table[i][j-1]};
                std::vector<Vertice> e = {v1, v2, v3, v4};
                graph.addEdge(v, e);
            }
        }
    }
    return graph;
}

Graph Map::groundGraph(Graph graph, Vertice start) {
    Graph subGraph = *new Graph();

    std::vector<Vertice> pile;
    std::vector<Vertice> marks = {};
    std::vector<Vertice> voisins = graph[start];
    
    subGraph.addEdge(start, voisins);
    pile.push_back(start);
    marks.push_back(start);
    // Tant que la pile n'est pas vide (toujours des sommets à visiter)
    while (pile.size() != 0) {
        // Récuperer le sommet
        Vertice sommet = pile.front();
        pile.erase(pile.begin());
        // Récuperer les voisins
        voisins = graph[sommet];
        for (Vertice v : voisins) {
            bool isMarked = false;
            for (Vertice mark : marks) {
                if ((v==mark)) {
                    isMarked=true;
                    break;
                }
            }
            if (!isMarked && v.indice != 4) {
                pile.push_back(v);
                marks.push_back(v);
                subGraph.addEdge(v, voisins);
            }
        }
    }
    return subGraph;
}

Graph Map::waterGraph(Graph graph, Vertice start) {
    Graph subGraph = *new Graph();
    
    std::vector<Vertice> pile;
    std::vector<Vertice> marks = {};
    std::vector<Vertice> voisins = graph[start];
    
    //subGraph.addEdge(start, voisins);
    pile.push_back(start);
    marks.push_back(start);
    // Tant que la pile n'est pas vide (toujours des sommets à visiter)
    while (pile.size() != 0) {
        // Récuperer le sommet
        Vertice sommet = pile.front();
        pile.erase(pile.begin());
        // Récuperer les voisins
        voisins = graph[sommet];
        for (Vertice v : voisins) {
            bool isMarked = false;
            for (Vertice mark : marks) {
                if ((v==mark)) {
                    isMarked=true;
                    break;
                }
            }
            if (!isMarked) {
                pile.push_back(v);
                marks.push_back(v);
            }
        }
        if (sommet.indice == 4) {
            subGraph.addEdge(sommet, voisins);
        }
    }
    return subGraph;
}

void Map::buildBridge(Graph g) {
    std::vector<std::pair<int,int>> pairs;
    // Tant que la pile n'est pas vide (toujours des sommets à visiter)
    for (std::pair<Vertice, std::vector<Vertice>> edge : g._edges) {
        int countWaterVoisin = 0;
        for (Vertice voisin : edge.second) {
            if (edge.first.indice != 4) break;
            if (voisin.indice == 4) countWaterVoisin++;
        }
        if (countWaterVoisin==2 and rand()%2==0) pairs.push_back(std::make_pair(edge.first.x,edge.first.y));
    }
    for (std::pair<int,int> pair : pairs) {
        _table[pair.first][pair.second] = 2;
    }
}
