//
//  Model.cpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 19/07/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#include "Model.h"

void Model::initialiseDucks() {
    for (int i = 0; i<_numberOfDucks; i++) {
        Canard *canard = new Canard(HealthyTexture);
        pushDuck(canard);
        canard->initialisePosition(_obstacles);
        _duck.addDuck(canard);
    }
}

void Model::initialiseObstacles() {
    std::vector<int> indices_vertices = _map->getVerticesIndices();
    for (int line=0; line<AREA_WIDTH; line++) {
        for (int column=0; column<AREA_HEIGHT; column++) {
            int index = column + line * AREA_HEIGHT;
            for (int tile : impassable) {
                if( indices_vertices[index] == tile) {
                    SDL_Rect obstacle = {
                        line * TILE_WIDTH,
                        column * TILE_HEIGHT,
                        TILE_WIDTH,
                        TILE_HEIGHT};
                    _obstacles.push_back(obstacle);
                    
                }
            }
        }
    }
}

void Model::initialiseFood() {
    _foods = {0, 0};
}

void Model::render(SDL_Renderer *render, int turn) {
    sortDucksDead();
    _map->render( render );
    #pragma omp parallel
    {
        #pragma omp for
        for (Canard *canard : _ducks) {
            canard->render(render, turn);
        }
    }
}

void Model::update(SDL_Renderer* render, int turnTime, LMouse* mouse) {
    
    //_duck.handle();
    // For each ducks
    for (Canard* target: _ducks) {
        bool locked = false;
        #pragma omp parallel
        {
            // For each others ducks
            #pragma omp for shared(model)
            for (Canard* other: _ducks) {
                
                float distanceBetweenTargetAndOhters = target->distanceBetween(*other);
                float YplusX = target->affineYplusX(*other);
                float YminusX = target->affineYminusX(*other);
                State otherState = other->getState();
                bool visionArc = false;
                bool detectionCircle = false;
                switch (target->getOrientation()) {
                    case UP:
                        detectionCircle = (target->getY() >= other->getY());
                        visionArc = (YminusX >= 0 && YplusX >= 0);
                        break;
                    case DOWN:
                        detectionCircle = (target->getY() <= other->getY());
                        visionArc = (YminusX <= 0 && YplusX <= 0);
                        break;
                    case LEFT:
                        detectionCircle = (target->getX() >= other->getX());
                        visionArc = (YminusX >= 0 && YplusX <= 0);
                        break;
                    case RIGHT:
                        detectionCircle = (target->getX() <= other->getX());
                        visionArc = (YminusX <= 0 && YplusX >= 0);
                        break;
                    default:
                        break;
                }

                switch (target->getState()) {
                    // Cas du canard en bonne santé
                    case HEALTHY:
                        // Le canard doit-il être engraissé ?
                        if (distanceBetweenTargetAndOhters <= DISTANCE_FOR_INFECT
                            and otherState == FATTY) {
                            target->setState(FATTY);
                            target->setTexture(FattyTexture);
                            target->setRatio(other->getRatio());
                            break;
                        }
                        // Le canard detecte-t-il un gros dans le coin-coin ;)
                        if (((distanceBetweenTargetAndOhters < DISTANCE_HEALTHY_DETECTION && detectionCircle)
                            || (distanceBetweenTargetAndOhters < DISTANCE_HEALTHY_VISION && visionArc))
                            && otherState == FATTY)
                        {
                            target->setState(STRESSED);
                            target->setSpeed(RUNNING_SPEED);
                            target->setTexture(StressedTexture);
                            target->setStress(100);
                            locked = true;
                        }
                        break;
                        
                    // Cas du canard cible engraissé
                    case FATTY:
                        // Si un canard non engraissé est dans les 36 alors courir tout droit
                        if (distanceBetweenTargetAndOhters < DISTANCE_FATTY_VISION
                            and otherState != FATTY and otherState != DEAD) {
                            bool hasSeenHealthy = false;
                            switch (target->getOrientation()) {
                                case DOWN:
                                    hasSeenHealthy = (target->sameX(*other)
                                                      and other->getY() >= target->getY());
                                    break;
                                case UP:
                                    hasSeenHealthy = (target->sameX(*other)
                                                      and other->getY() <= target->getY());
                                    
                                    break;
                                case LEFT:
                                    hasSeenHealthy = (target->sameY(*other)
                                                      and other->getX() <= target->getX());
                                    break;
                                case RIGHT:
                                    hasSeenHealthy = (target->sameY(*other)
                                                      and other->getX() >= target->getX());
                                    break;
                                default: break;
                            }
                            if (hasSeenHealthy) {
                                target->setSpeed(RUNNING_SPEED);
                                locked = true;
                            }
                        }
                        // Si aucune canard différent d'engraissé dans les 36 alors marché
                        if (not locked)
                            target->setSpeed(NORMAL_SPEED);
                        break;
                    case STRESSED:
                        // Si la distance est inférieur à 20 et l'autre est engraissé
                        // Alors on engraisse ce canard
                        if (distanceBetweenTargetAndOhters <= DISTANCE_FOR_INFECT
                            and otherState == FATTY) {
                            target->setState(FATTY);
                            target->setTexture(FattyTexture);
                            target->setRatio(other->getRatio());
                            break;
                        }
                        // Si le stress est redescendu alors il est en bonne santé
                        if (target->getStress() < 0) {
                            target->setTexture(HealthyTexture);
                            target->setState(HEALTHY);
                            target->setSpeed(NORMAL_SPEED);
                        }
                    case DEAD:
                        break;
                        break;
                    default:
                        break;
                }
            }
        }
        
        // Temporary Conditional for testing food
        /*
        if (rand()%100 > 98
            and _foods.size() != 0) {
            std::cout << "A duck has eaten a vitamin" << std::endl;
            Food* food = _foods[rand() % _foods.size()];
            if (target->gulpDown(*food))
                target->setTexture(FattyTexture);
            //target->render(render, timeStep);
            eraseFood(food);
            delete food;
            food = nullptr;
        }*/
        SDL_Rect source = target->getCollider();
        int x = (source.x - mouse->getX());
        int y = (source.y - mouse->getY());
        float distance = sqrtf(x*x + y*y);
        if (distance < mouse->realRadius() && mouse->isPressed()) {
            mouse->switchOffButton();
            Food* food = nullptr;
            switch (mouse->getStatus()) {
                case VITAMIN:
                    if (_foods[(int)VITAMIN] < 1) {
                        food = new Vitamin();
                        increaseFood((int)VITAMIN);
                    }
                    break;
                case WHEAT:
                    if (_foods[(int)WHEAT] < 1) {
                        food = new Wheat();
                        increaseFood((int)WHEAT);
                    }
                    break;
                default:
                    break;
            }
            if (food != nullptr) {
                if (target->gulpDown(*food))
                    target->setTexture(FattyTexture);
                delete food;
                food = nullptr;
            }
        }
        
        target->update(turnTime, _obstacles, locked);
        int duckWeight = target->getWeight();
        if ((duckWeight > target->getMaximum() or duckWeight < target->getMinimum()) and target->getState() != DEAD) {
            target->setState(DEAD);
            target->setTexture(DeadTexture);
            std::cout << "A duck has been slained" << std::endl;
        }
    }
}
