//
//  DGrid.cpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 10/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#include "DGrid.hpp"
#include "Canard.h"

void DGrid::addDuck(Canard* canard) {
    // Determine which grid cell it's in.
    int cellX = (int)(canard->getX() / DGrid::CELL_SIZE);
    int cellY = (int)(canard->getY() / DGrid::CELL_SIZE);
    
    // Add to the front of list for the cell it's in.
    canard->setPrev(nullptr);
    canard->setNext(_cells[cellX][cellY]);
    _cells[cellX][cellY] = canard;
    
    if (canard->getNext() != nullptr)
    {
        canard->getNext()->setPrev(canard);
    }
}

void DGrid::moveDuck(Canard* unit, int x, int y) {
    // See which cell it was in.
    int oldCellX = (int)(unit->getX() / DGrid::CELL_SIZE);
    int oldCellY = (int)(unit->getY() / DGrid::CELL_SIZE);
    
    // See which cell it's moving to.
    int cellX = (int)(x / DGrid::CELL_SIZE);
    int cellY = (int)(y / DGrid::CELL_SIZE);
    
    unit->setX(x);
    unit->setY(y);
    
    // If it didn't change cells, we're done.
    if (oldCellX == cellX && oldCellY == cellY) return;
    
    // Unlink it from the list of its old cell.
    if (unit->getPrev() != nullptr)
    {
        unit->getPrev()->setNext(unit->getNext());
    }
    
    if (unit->getNext() != nullptr)
    {
        unit->getNext()->setPrev(unit->getPrev());
    }
    // If it's the head of a list, remove it.
    if (_cells[oldCellX][oldCellY] == unit)
    {
        _cells[oldCellX][oldCellY] = unit->getNext();
    }
    
    // Add it back to the grid at its new cell.
    addDuck(unit);
}

void DGrid::handle() {
    for (int i=0; i < DGrid::WIDTH_NUM_CELLS; i++) {
        for(int j=0; j < DGrid::HEIGHT_NUM_CELLS; j++) {
            handleCell(i, j);
        }
    }
}

void DGrid::handleDuck(Canard* canard) {
    while (canard != nullptr) {
        Canard* other = canard->_next;
        while (other != nullptr) {
            if (distance(canard, other) < DISTANCE_FOR_INFECT) {
                handleDucks(canard, other);
            }
            other = other->_next;
        }
    }
}

void DGrid::handleCell(int x, int y) {
    Canard* unit = _cells[x][y];
    while (unit != nullptr) {
        // Handle Weight
        
        
        // Handle other units in this cell.
        handleDucks(unit, unit->getNext());
        
        // Also try the neighboring cells.
        if (x > 0 && y > 0) handleDucks(unit, _cells[x - 1][y - 1]);
        if (x > 0 && y < HEIGHT_NUM_CELLS - 1) {
            handleDucks(unit, _cells[x - 1][y + 1]);
        }
        if (x < WIDTH_NUM_CELLS - 1 && y > 0) {
            handleDucks(unit, _cells[x + 1][y - 1]);
        }
        if (x < WIDTH_NUM_CELLS - 1 && y < HEIGHT_NUM_CELLS - 1) {
            handleDucks(unit, _cells[x + 1][y + 1]);
        }
        if (x > 0) handleDucks(unit, _cells[x - 1][y]);
        if (y > 0) handleDucks(unit, _cells[x][y - 1]);
        if (x < WIDTH_NUM_CELLS - 1) handleDucks(unit, _cells[x + 1][y]);
        if (y < HEIGHT_NUM_CELLS - 1) handleDucks(unit, _cells[x][y + 1]);

        unit = unit->getNext();
    }
}

void DGrid::handleDucks(Canard* target, Canard* other) {
    while (other != nullptr) {
        if (distance(target, other) < DISTANCE_FOR_INFECT) {
            if (other->getState() == FATTY) {
                target->setState(FATTY);
                //target->setTexture(Model::FattyTexture);
                target->setRatio(other->getRatio());
            }
        }
        other = other->getNext();
    }
}

float DGrid::distance(Canard* target, Canard* other) {
    float targetX = target->getX();
    float targetY = target->getY();
    float ohterX = other->getX();
    float otherY = other->getY();
    float x_diff = (targetX - ohterX);
    float y_diff = (targetY - otherY);
    return sqrt(x_diff * x_diff + y_diff * y_diff);
}
