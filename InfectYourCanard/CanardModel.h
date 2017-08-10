//
//  CanardModel.h
//  InfectYourCanard
//
//  Created by Remi DECELLE on 07/08/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#ifndef CanardModel_h
#define CanardModel_h

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Common.h"
#include "LTexture.h"

class CanardModel {
private:
    LTexture _texture;
    
public:
    CanardModel();
    ~CanardModel();
};
#endif /* CanardModel_h */
