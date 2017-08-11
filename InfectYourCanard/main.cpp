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
#include "LMouse.hpp"
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
    
    //int zone = rand()%3;
    int zone = 2;
    // Initialise all pointers
    Mix_Music *music = nullptr;
    FileManager *fileManager = nullptr;
    Model *model = nullptr;
    SDL_Event* event = nullptr;
    LMouse* mouse = nullptr;
    Mix_Chunk* sound = nullptr;
    
    // Model creation
    if (zone == 0) fileManager = new FileManager("./resources/map/Mountain.txt");
    if (zone == 1) fileManager = new FileManager("./resources/map/Hills.txt");
    if (zone == 2) fileManager = new FileManager("./resources/map/Vulcano.txt");
    
    model = new Model(render);
    fileManager->readMap(model);
    delete fileManager;
    model->generativeMap(zone);
    model->makeMap("./resources/image/Tileset.png", render);
    // Initialise Obstacles for the model (all sprite that can't be passed)
    model->initialiseObstacles();
    model->initialiseDucks();
    model->initialiseFood();
    
    // Mouse Creation
    mouse = new LMouse();
    mouse->setRadius(TILE_WIDTH);
    SDL_Surface* mouseSurfaceVitamin = IMG_Load("./resources/image/MouseVitamin.png");
    SDL_Surface* mouseSurfaceWheat = IMG_Load("./resources/image/MouseWheat.png");
    mouse->setCursor(mouseSurfaceVitamin);
    while (SDL_ShowCursor(SDL_ENABLE) != SDL_ENABLE) {};
    SDL_SetCursor(NULL);
    int turn = 0;
    LTimer stepTimer;

    // Music initialse
    Mix_OpenAudio(8000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 64);
    if (zone == 0) music = Mix_LoadMUS("./resources/audio/Hills.mid");
    if (zone == 1) music = Mix_LoadMUS("./resources/audio/Mountain.mid");
    if (zone == 2) music = Mix_LoadMUS("./resources/audio/Vulcano.mid");
    
    if (!Mix_PlayingMusic()) {
        Mix_PlayMusic(music, -1);
        Mix_VolumeMusic(MIX_MAX_VOLUME/6);
    }
    sound = Mix_LoadWAV("./resources/audio/duckSound.wav");
    
    event = new SDL_Event();
    bool quit = false;
    while(!quit) {
        float timeStep = stepTimer.getTicks() / 1000.f;
        model->updateTimer(timeStep);
        SDL_SetCursor(NULL);
        while (SDL_PollEvent(event)) {
            switch (event->type) {
                case SDL_QUIT:
                    SDL_Quit();
                    exit(0);
                    break;
                case SDL_MOUSEMOTION:
                    mouse->setPosition(event->motion.x,event->motion.y);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mouse->setPosition(event->motion.x,event->motion.y);
                    if (model->moreThanOneFood(mouse->getStatus())) {
                        std::cout << model->foodAt(mouse->getStatus()) << std::endl;
                        Mix_PlayChannel(1, sound, 0);
                    }
                    else
                        mouse->switchOnButton();
                    break;
                case SDL_MOUSEWHEEL:
                    mouse->switchStatus();
                    switch (mouse->getStatus()) {
                        case VITAMIN:
                            mouse->setCursor(mouseSurfaceVitamin);
                            mouse->setRadius(64.00f);
                            break;
                        case WHEAT:
                            mouse->setCursor(mouseSurfaceWheat);
                            mouse->setRadius(48.00f);
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }
        // Update Model
        if (model->getCanards().size() == 0)
            break;

        model->update(render, timeStep, mouse);
        
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
        if (model->getTimer() < 0) quit = true;
    }
    SDL_Delay(1000);
    for (Canard* canard : model->getCanards()) {
        if (canard->getState() == DEAD) {
           model->addScore(canard->getWeight());
        }
        model->eraseDuck(canard);
    }
    std::cout << "Gramme de foie gras : \n" << model->getScore() << std::endl;
    // Destroy renderer
    SDL_DestroyRenderer(render);
    render = nullptr;
    
    //Destroy window
    SDL_DestroyWindow( window );
    window = nullptr;
    
    //Quit SDL subsystems
    SDL_Quit();
    // insert code here...
    return 0;
}
