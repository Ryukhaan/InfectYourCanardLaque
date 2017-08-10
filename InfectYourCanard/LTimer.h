//
//  LTimer.h
//  InfectYourCanard
//
//  Created by Remi DECELLE on 29/07/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#ifndef LTimer_h
#define LTimer_h

#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

class LTimer
{
public:
    //Initializes variables
    LTimer();
    
    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();
    
    //Gets the timer's time
    Uint32 getTicks();
    
    //Checks the status of the timer
    bool isStarted();
    bool isPaused();
    
private:
    //The clock time when the timer started
    Uint32 _startTicks;
    
    //The ticks stored when the timer was paused
    Uint32 _pausedTicks;
    
    //The timer status
    bool _paused;
    bool _started;
    bool _initialized;
};


#endif /* LTimer_hpp */
