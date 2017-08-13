//
//  LTexture.cpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 23/07/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#include "LTexture.h"


LTexture::LTexture()
    : _texture(nullptr)
    , mWidth(TILE_WIDTH)
    , mHeight(TILE_HEIGHT)
{}

LTexture::LTexture(const std::string &path, SDL_Renderer *renderer)
    : _texture(nullptr)
    , mWidth(TILE_WIDTH)
    , mHeight(TILE_HEIGHT)
{
    //Initialize
    loadFromFile(path, renderer);
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile(const std::string &path, SDL_Renderer* gRenderer )
{
    //The final texture
    //SDL_Texture* texture = nullptr;
    //Load image at specified path
    SDL_Surface* loadedImage = IMG_Load( path.c_str() );
    if( loadedImage != nullptr )
    {
        if (_texture != nullptr)
             _texture = nullptr;
        _texture = SDL_CreateTextureFromSurface(gRenderer, loadedImage);
        SDL_FreeSurface(loadedImage);
        if ( _texture == nullptr)
                std::cout << "CreateTextureFromSurface failure" << std::endl;
    }
    else
    {
        //logSDLError(std::cout, "LoadImage");
        std::cout << "Image unloaded : " << path << std::endl;
    }
    return true;
}

void LTexture::free()
{
    //Free texture if it exists
    if( _texture != nullptr )
    {
        SDL_DestroyTexture( _texture );
        _texture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( _texture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( _texture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( _texture, alpha );
}

void LTexture::render( SDL_Renderer* gRenderer, SDL_Rect *source, int x, int y )
{
    //Set rendering space and render to screen
    SDL_Rect destination = { x, y, mWidth, mHeight };

    //Render to screen
    if (source != nullptr) {
        destination.w = source->w;
        destination.h = source->h;
    }
    else
        SDL_QueryTexture(_texture, NULL, NULL, &destination.w, &destination.h);
    SDL_RenderCopy( gRenderer, _texture, source, &destination );
    //SDL_RenderDrawRect( gRenderer, &source);
}

void LTexture::createFromSurface(SDL_Renderer *renderer, SDL_Surface *surface) {
    _texture = SDL_CreateTextureFromSurface(renderer, surface);
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

void LTexture::setWidth(int width){
    mWidth = width;
}

void LTexture::setHeight(int height) {
    mHeight = height;
}



