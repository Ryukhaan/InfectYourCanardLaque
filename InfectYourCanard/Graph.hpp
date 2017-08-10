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
    bool operator== (const Vertice v) {return (v.x==x && v.y==y);};
};

class Graph {
private:
    int _size;
    
public:
    std::vector<std::pair<Vertice, std::vector<Vertice>>> _edges;

    Graph(): _size(0) {_edges = {};};
    
    std::vector<Vertice> operator[] (const Vertice elem) {
        for (std::pair<Vertice, std::vector<Vertice>> edge : _edges) {
            if (edge.first == elem)
                return edge.second;
        }
        return {};
    }
    
    bool has (const Vertice elem) {
        for (std::pair<Vertice, std::vector<Vertice>> edge : _edges) {
            if (edge.first == elem)
                return true;
        }
        return false;
    };
    
    int size() {
        return _size;
    };
    void addEdge(Vertice v, std::vector<Vertice> e) {
        _edges.push_back(std::make_pair(v, e));
        _size ++;
    }
    
};

#endif /* Graph_hpp */
