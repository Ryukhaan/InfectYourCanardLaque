//
//  LTexture.h
//  InfectYourCanard
//
//  Created by Remi DECELLE on 23/07/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#ifndef LTexture_h
#define LTexture_h

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "Common.h"

//Texture wrapper class
//Texture wrapper class
class LTexture
{
public:
    //Initializes variables
    LTexture();
    LTexture(const std::string &path, SDL_Renderer *renderer);
    
    //Deallocates memory
    ~LTexture();
    
    //Loads image at specified path
    bool loadFromFile(const std::string &path, SDL_Renderer* gRenderer );
    
    //Deallocates texture
    void free();
    
    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    
    //Set blending
    void setBlendMode( SDL_BlendMode blending );
    
    //Set alpha modulation
    void setAlpha( Uint8 alpha );
    
    //Renders texture at given point
    void render( SDL_Renderer* gRenderer, SDL_Rect *source, int x, int y);
    
    //Gets image dimensions
    int getWidth();
    int getHeight();
    
    //Sets image dimensions
    void setWidth(int width);
    void setHeight(int height);
    
    //Creates Texture from a surface (maps)
    void createFromSurface(SDL_Renderer* renderer, SDL_Surface* surface);
    
private:
    //The actual hardware texture
    SDL_Texture* _texture;
    //SDL_Surface* _texture;
    
    //Image dimensions
    int mWidth;
    int mHeight;
};

#endif /* LTexture_hpp */
