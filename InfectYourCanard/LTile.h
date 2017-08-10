//
//  LTile.h
//  InfectYourCanard
//
//  Created by Remi DECELLE on 29/07/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#ifndef LTile_h
#define LTile_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

class LTile {
private:
    SDL_Rect _collider;
    
public:
    LTile();
    ~LTile();
    
    // Getters
    SDL_Rect getCollider();
    int getNumber();
    
    // Setters
    void setCollider();
    void setNumber();
};
#endif /* LTile_hpp */
