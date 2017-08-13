//
//  Graph.cpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 07/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#include "Graph.hpp"

void Graph::removeTile(LTile tile) {
    for (int neighbor : tile._neighbors) {
        for (LTile other: _vertices) {
            if (other._id == neighbor) {
                // Remove neighbor in other._neighbors
                other._neighbors.erase(std::remove(
                                        other._neighbors.begin(),
                                        other._neighbors.end(),
                                        tile._id),
                                       other._neighbors.end());
            }
        }
    }
    _vertices.erase(std::remove(_vertices.begin(), _vertices.end(), tile), _vertices.end());
    _size--;
}

void Graph::setGraphFromTable(std::vector<int> table) {
    std::function<int (int, int)> toward = [](int x, int y) {return x * AREA_HEIGHT + y;};
    _vertices.clear();
    _size = 0;
    for (int i=0; i<AREA_WIDTH; i++) {
        for (int j=0; j<AREA_HEIGHT; j++) {
            int index = toward(i,j);
            int indice = 0;
            if (table.size() != 0) indice = table[index];
            LTile v = {index, indice};
            // Up Left Corner
            if (i==0 && j==0) {
                int v1 = toward(i+1, j);
                int v2 = toward(i, j+1);
                std::vector<int> e = {v1, v2};
                addEdge(v, e);
            }
            // Up Right Corner
            else if (i==AREA_WIDTH-1 && j==0) {
                int v1 = toward(i-1, j);
                int v2 = toward(i, j+1);
                std::vector<int> e = {v1, v2};
                addEdge(v, e);
            }
            // Down Left Corner
            else if (i==0 && j==AREA_HEIGHT-1) {
                int v1 = toward(i+1, j);
                int v2 = toward(i, j-1);
                std::vector<int> e = {v1, v2};
                addEdge(v, e);
            }
            // Down Right Corner
            else if (i==AREA_WIDTH-1 && j==AREA_HEIGHT-1) {
                int v1 = toward(i-1, j);
                int v2 = toward(i, j-1);
                std::vector<int> e = {v1, v2};
                addEdge(v, e);
            }
            // Left Border
            else if (i==0) {
                int v1 = toward(i+1, j);
                int v2 = toward(i, j+1);
                int v3 = toward(i, j-1);
                std::vector<int> e = {v1, v2, v3};
                addEdge(v, e);
            }
            // Right Border
            else if (i==AREA_WIDTH-1) {
                int v1 = toward(i-1, j);
                int v2 = toward(i, j+1);
                int v3 = toward(i, j-1);
                std::vector<int> e = {v1, v2, v3};
                addEdge(v, e);
            }
            // Up Border
            else if (j==0) {
                int v1 = toward(i+1, j);
                int v2 = toward(i-1, j);
                int v3 = toward(i, j+1);
                std::vector<int> e = {v1, v2, v3};
                addEdge(v, e);
            }
            // Down Border
            else if (j==AREA_HEIGHT-1) {
                int v1 = toward(i+1, j);
                int v2 = toward(i-1, j);
                int v3 = toward(i, j-1);
                std::vector<int> e = {v1, v2, v3};
                addEdge(v, e);
            }
            // Normal case
            else {
                int v1 = toward(i+1, j);
                int v2 = toward(i-1, j);
                int v3 = toward(i, j+1);
                int v4 = toward(i, j-1);
                std::vector<int> e = {v1, v2, v3, v4};
                addEdge(v, e);
            }
        }
    }
}
