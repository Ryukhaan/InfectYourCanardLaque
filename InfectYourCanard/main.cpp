//
//  main.cpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 18/07/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <unistd.h>
//#include <omp.h>
#include "FileManager.h"
#include "LTimer.h"
#include "Canard.h"
#include "Food.h"
#include "Vitamin.h"
#include "Wheat.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>

#define RATE_FRAME 30

void contamine(int data) {
    printf("Running thread with value = %d\n", data);
}

int main(int argc, const char * argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    /* Create a Window */
    SDL_Window *window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    /* Create a Render */
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (render == nullptr) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    //SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
    SDL_UpdateWindowSurface( window );
    
    //SDL_Surface* tileset= IMG_Load("resources/image/Tileset.png");
    
    srand (time(NULL));
    
    // Load Map's Model
    FileManager *fileManager = new FileManager("./resources/map/Map_Moutain_2.txt");
    Model *model = new Model(render);
    fileManager->readMap(model);
    std::cout << "File Management Done \n";
    delete fileManager;
    
    SDL_Event* event = new SDL_Event();
    int* mouseX = nullptr;
    int* mouseY = nullptr;
    SDL_Cursor* mouseCursor = nullptr;
    SDL_Surface* cheeseSurface = IMG_Load("./resources/image/CheeseArea.png");
    SDL_Surface* cakeSurface = IMG_Load("./resources/image/CakeArea.png");
    SDL_Surface* sodaSurface = IMG_Load("./resources/image/SodaArea.png");
    SDL_Surface* hamburgerSurface = IMG_Load("./resources/image/HamburgerArea.png");
    
    model->generativeMap();
    model->makeMap("resources/image/Tileset.png", render);

    // Initialise Obstacles for the model (all sprite that can't be passed)
    model->initialiseObstacles();
    model->initialiseDucks();
    std::vector<SDL_Rect> obstacles = model->getObstacles();
    
    Wheat *wheat = new Wheat();
    //Vitamin *wheat = new Vitamin();
    model->pushFood(wheat);
    //Vitamin *wheat = new Vitamin();

    int turn = 0;
    LTimer stepTimer;
    SDL_Rect mouseRect;
    // Music
    Mix_OpenAudio(8000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 64);
    Mix_Music *music;
    music = Mix_LoadMUS("./resources/audio/MusicInGame_Prairie.mid");
    if (!Mix_PlayingMusic()) {
        Mix_PlayMusic(music, -1);
        Mix_VolumeMusic(MIX_MAX_VOLUME/6);
    }
    Mix_Chunk* sound = Mix_LoadWAV("./resources/audio/duckSound.wav");;
    
    float timer = 20.0;
    bool quit = false;
    while(!quit) {
        float timeStep = stepTimer.getTicks() / 1000.f;
        timer -= timeStep;
        
        while (SDL_PollEvent(event)) {
            switch (event->type) {
                case SDL_QUIT:
                    SDL_Quit();
                    exit(0);
                    break;
                case SDL_MOUSEMOTION:
                    mouseX = &event->motion.x;
                    mouseY = &event->motion.y;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (model->sizeFood() == 0)
                        Mix_PlayChannel(1, sound, 0);
                    else
                        mouseRect = {*mouseX, *mouseY, 4*TILE_WIDTH, 4*TILE_HEIGHT};
                    break;
                case SDL_KEYDOWN:
                    switch (event->key.keysym.sym) {
                        case SDLK_a:
                            mouseCursor = SDL_CreateColorCursor(cheeseSurface, 0, 0);
                            break;
                        case SDLK_z:
                            mouseCursor = SDL_CreateColorCursor(sodaSurface, 0, 0);
                            break;
                        case SDLK_e:
                            mouseCursor = SDL_CreateColorCursor(cakeSurface, 0, 0);
                            break;
                        case SDLK_r:
                            mouseCursor = SDL_CreateColorCursor(hamburgerSurface, 0, 0);
                            break;
                        default:
                            break;
                    }
                    SDL_SetCursor(mouseCursor);
                    break;

                default:
                    break;
            }
        }
        // Update Model
        if (model->getCanards().size() == 0)
            break;

        model->update(render, timeStep, mouseRect);
        
        // Restart step timer
        stepTimer.start();
        
        // Clear screen
        //SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( render );
        
        // Render model
        model->render(render, turn/16+1);

        //Update screen
        SDL_RenderPresent( render );
        
        SDL_Delay(12);
        turn = (turn + 1) % 32;
        if (timer < 0) quit = true;
    }
    SDL_Delay(1500);
    for (Canard* canard : model->getCanards()) {
        if (canard->getState() == DEAD) {
           model->addScore(canard->getWeight());
        }
        model->eraseDuck(canard);
    }
    std::cout << model->getScore() << std::endl;
    // Destroy renderer
    SDL_DestroyRenderer(render);
    render = nullptr;
    
    //Destroy window
    SDL_DestroyWindow( window );
    window = nullptr;
    
    //Quit SDL subsystems
    SDL_Quit();
    // insert code here...
    std::cout << "Hello, World!\n";
    
    return 0;
}
