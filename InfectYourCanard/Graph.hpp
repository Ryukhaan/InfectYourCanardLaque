//
//  Graph.hpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 07/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <vector>
#include "Common.h"

class Vertice {
public:
    int x,y;
    int indice;
    std::vector<Vertice *> neighbors;
    bool operator== (const Vertice v) {return (v.x==x && v.y==y);};
    
    Vertice(int i, int j, int idx) {
        x = i;
        y = j;
        indice = idx;
        neighbors = {};
    }
    Vertice(int i, int j, std::vector<int> table) {
        x = i;
        y = j;
        table.size()==0 ? indice = 0 : indice = table[i * AREA_HEIGHT + j];
    }
};

class Graph {
private:
    int _size;
    
public:
    std::vector<Vertice> _edges;

    Graph(): _size(0) {_edges = {};};
    
    /*
    std::vector<Vertice> operator[] (const Vertice elem) {
        for (std::pair<Vertice, std::vector<Vertice>> edge : _edges) {
            if (edge.first == elem)
                return edge.second;
        }
        return {};
    }*/
    
    std::vector<Vertice*> neighbors(const Vertice elem) const {
        return elem.neighbors;
    }
    
    bool has(const Vertice elem) {
        for (Vertice edge : _edges) {
            if (edge == elem)
                return true;
        }
        return false;
    };
    
    int size() {
        return _size;
    };
    
    void addEdge(Vertice v, const std::vector<Vertice*> e) {
        v.neighbors = e;
        _edges.push_back(v);
        _size ++;
    }
    
    
    std::vector<int> convertGraphToTable() {
        std::vector<int> table;
        for (Vertice edge : _edges) {
            table.push_back(edge.indice);
        }
        return table;
    }
    
    void setGraphFromTable(std::vector<int> table) {
        _edges.clear();
        _size = 0;
        for (int i=0; i<AREA_WIDTH; i++) {
            for (int j=0; j<AREA_HEIGHT; j++) {
                int index = i * AREA_HEIGHT + j;
                int indice = 0;
                if (table.size() != 0) indice = table[index];
                Vertice v = {i, j, indice};
                // Up Left Corner
                if (i==0 && j==0) {
                    Vertice v1 = {i+1, j, table};
                    Vertice v2 = {i, j+1, table};
                    std::vector<Vertice*> e = {&v1, &v2};
                    addEdge(v, e);
                }
                // Up Right Corner
                else if (i==AREA_WIDTH-1 && j==0) {
                    Vertice v1 = {i-1, j, table};
                    Vertice v2 = {i, j+1, table};
                    std::vector<Vertice*> e = {&v1, &v2};
                    addEdge(v, e);
                }
                // Down Left Corner
                else if (i==0 && j==AREA_HEIGHT-1) {
                    Vertice v1 = {i+1, j, table};
                    Vertice v2 = {i, j-1, table};
                    std::vector<Vertice*> e = {&v1, &v2};
                    addEdge(v, e);
                }
                // Down Right Corner
                else if (i==AREA_WIDTH-1 && j==AREA_HEIGHT-1) {
                    Vertice v1 = {i-1, j, table};
                    Vertice v2 = {i, j-1, table};
                    std::vector<Vertice*> e = {&v1, &v2};
                    addEdge(v, e);
                }
                // Left Border
                else if (i==0) {
                    Vertice v1 = {i+1, j, table};
                    Vertice v2 = {i, j+1, table};
                    Vertice v3 = {i, j-1, table};
                    std::vector<Vertice*> e = {&v1, &v2, &v3};
                    addEdge(v, e);
                }
                // Right Border
                else if (i==AREA_WIDTH-1) {
                    Vertice v1 = {i-1, j, table};
                    Vertice v2 = {i, j+1, table};
                    Vertice v3 = {i, j-1, table};
                    std::vector<Vertice*> e = {&v1, &v2, &v3};
                    addEdge(v, e);
                }
                // Up Border
                else if (j==0) {
                    Vertice v1 = {i+1, j, table};
                    Vertice v2 = {i-1, j, table};
                    Vertice v3 = {i, j+1, table};
                    std::vector<Vertice*> e = {&v1, &v2, &v3};
                    addEdge(v, e);
                }
                // Down Border
                else if (j==AREA_HEIGHT-1) {
                    Vertice v1 = {i+1, j, table};
                    Vertice v2 = {i-1, j, table};
                    Vertice v3 = {i, j-1, table};
                    std::vector<Vertice*> e = {&v1, &v2, &v3};
                    addEdge(v, e);
                }
                // Normal case
                else {
                    Vertice v1 = {i+1, j, table};
                    Vertice v2 = {i-1, j, table};
                    Vertice v3 = {i, j+1, table};
                    Vertice v4 = {i, j-1, table};
                    std::vector<Vertice*> e = {&v1, &v2, &v3, &v4};
                    addEdge(v, e);
                }
            }
        }
    }
};

#endif /* Graph_hpp */
