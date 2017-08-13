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
        _ducks.push_back(canard);
        canard->initialisePosition(_obstacles);
        //_duck.addDuck(canard);
    }
}

void Model::initialiseObstacles() {
    Graph graph  = _map->getGraph();
    for (LTile tile : graph._vertices) {
        int line = tile._id  / AREA_HEIGHT;
        int column = tile._id % AREA_HEIGHT;
        if( !tile._passable ) {
            SDL_Rect obstacle = {
                line * TILE_WIDTH,
                column * TILE_HEIGHT,
                TILE_WIDTH,
                TILE_HEIGHT};
            _obstacles.push_back(obstacle);
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
        State* targetState = target->getState();
        bool locked = false;
        #pragma omp parallel
        {
            // For each others ducks
            #pragma omp for shared(model)
            for (Canard* other: _ducks) {
                
                float distanceBetweenTargetAndOhters = target->distanceBetween(*other);
                float YplusX = target->affineYplusX(*other);
                float YminusX = target->affineYminusX(*other);
                State* otherState = other->getState();
                bool visionArc = false;
                bool detectionCircle = false;
                bool hasSeenHealthy = false;
                switch (targetState->getOrientation()) {
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

                switch (targetState->getID()) {
                    // Cas du canard en bonne santé
                    case 0:
                        // Le canard doit-il être engraissé ?
                        if (distanceBetweenTargetAndOhters <= DISTANCE_FOR_INFECT
                            and otherState->getID() == 2) {
                            target->fatty();
                            target->setTexture(FattyTexture);
                            target->setRatio(other->getRatio());
                            break;
                        }
                        // Le canard detecte-t-il un gros dans le coin-coin ;)
                        if (((distanceBetweenTargetAndOhters < DISTANCE_HEALTHY_DETECTION && detectionCircle)
                            || (distanceBetweenTargetAndOhters < DISTANCE_HEALTHY_VISION && visionArc))
                            && otherState->getID() == 2)
                        {
                            target->stressed();
                            target->setSpeed(RUNNING_SPEED);
                            target->setTexture(StressedTexture);
                            //target->setStress(100);
                            locked = true;
                        }
                        break;
                        
                    // Cas du canard cible engraissé
                    case 2: // FATTY
                        // Si un canard non engraissé est dans les 36 alors courir tout droit
                        if (distanceBetweenTargetAndOhters < DISTANCE_FATTY_VISION
                            and otherState->getID() != 2 and otherState->getID() != -1) {
                            switch (targetState->getOrientation()) {
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
                    case 1: // STRESSED
                        // Si la distance est inférieur à 20 et l'autre est engraissé
                        // Alors on engraisse ce canard
                        if (distanceBetweenTargetAndOhters <= DISTANCE_FOR_INFECT
                            and otherState->getID() == 2) {
                            target->fatty();
                            target->setTexture(FattyTexture);
                            target->setRatio(other->getRatio());
                            break;
                        }
                        // Si le stress est redescendu alors il est en bonne santé
                        if ( ((StressState*)targetState)->getStress() < 0) {
                            target->setTexture(HealthyTexture);
                            target->healthy();
                            target->setSpeed(NORMAL_SPEED);
                        }
                    case -1: // DEAD
                        break;
                        break;
                    default:
                        break;
                }
                if (hasSeenHealthy)
                    break;
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
            FoodStuff* feed = mouse->getFeed();
            int index = feed->getID();
            if (feed != nullptr && _foods[index]<1) {
                if (target->getState()->gulp(feed)) {
                    target->fatty();
                    target->setTexture(FattyTexture);
                }
                _foods[index] ++;
            }
        }
        
        target->update(turnTime, _obstacles, locked);
        State* state = target->getState();
        int duckWeight = state->getWeight();
        if ((duckWeight > state->getMaximum() or duckWeight < state->getMinimum()) and state->getID() != -1) {
            target->dead();
            target->setTexture(DeadTexture);
            std::cout << "A duck has been slained" << std::endl;
        }
    }
}
