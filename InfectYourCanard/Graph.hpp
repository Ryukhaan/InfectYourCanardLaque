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
#include "LTile.h"

class Graph {
private:
    int _size;
    
public:
    std::vector<LTile> _vertices;

    Graph()
    : _size(0)
    , _vertices({})
    {};
    
    std::vector<int> neighbors(const LTile elem) {
        return elem._neighbors;
    }
    
    std::vector<int> neighbors(const int num) {
        for (LTile vertice : _vertices)
            if (vertice._id == num)
                return vertice._neighbors;
        return {};
    }
    
    bool has(const LTile elem) {
        for (LTile vertex : _vertices) {
            if (vertex == elem)
                return true;
        }
        return false;
    };
    
    int size() {
        return _size;
    };
    
    void addEdge(LTile vertice, std::vector<int> neighbors) {
        vertice._neighbors = neighbors;
        _vertices.push_back(vertice);
        _size ++;
    }
    
    void addTile(LTile tile) {
        _vertices.push_back(tile);
        _size ++;
    }
    
    LTile getTile(int num) {
        for (LTile tile : _vertices)
            if (tile._id == num)
                return tile;
        return {};
    }
    
    std::vector<int> convertGraphToTable() {
        std::vector<int> table;
        for (LTile vertice : _vertices) {
            table.push_back(vertice._id);
        }
        return table;
    }
    
    void removeTile(LTile tile);
    void setGraphFromTable(std::vector<int> table);
};

#endif /* Graph_hpp */
