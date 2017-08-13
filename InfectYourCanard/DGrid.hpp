//
//  DGrid.hpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 10/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#ifndef DGrid_hpp
#define DGrid_hpp

#include <stdio.h>
#include "Canard.h"

class DGrid {
    friend class Model;
public:
    static const int WIDTH_NUM_CELLS = AREA_WIDTH;
    static const int HEIGHT_NUM_CELLS = AREA_HEIGHT;
    static const int CELL_SIZE = TILE_WIDTH;
    
    DGrid() {
        for (int i=0; i<WIDTH_NUM_CELLS; i++) {
            for (int j=0; j<HEIGHT_NUM_CELLS; j++) {
                _cells[i][j] = nullptr;
            }
        }
    }
    
    void addDuck(Canard* canard);
    void moveDuck(Canard* canard, int x, int y);
    void handle();
    void handleDuck(Canard* canard);
    void handleCell(int x, int y);
    void handleDucks(Canard* target, Canard* other);
    float distance(Canard* target, Canard* other);
    
private:
    Canard* _cells[WIDTH_NUM_CELLS][HEIGHT_NUM_CELLS];
};
#endif /* DGrid_hpp */
