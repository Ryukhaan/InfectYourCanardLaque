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
#include "Common.h"

class LTile {
public:
    enum BrushType {
        palmtree    = 0,
        tree        = 1,
        bridge      = 2,
        grass       = 3,
        river       = 4,
        rock        = 5,
        ground      = 6,
        lava        = 7,
        cooledlava  = 8,
        swamp       = 20,
        humus       = 21,
        bramble     = 22,
        pine        = 23,
        darkgrass   = 24,
        snowtree    = 25,
        snow        = 26,
        iceblock    = 27,
        sand        = 28,
    };
    
    int _id;
    bool _passable;
    BrushType _type;
    std::vector<int> _neighbors;
    
    LTile() {};
    LTile(int i, int type) {
        _id = i;
        _type = (BrushType) type;
        switch (type) {
            case palmtree:
            case tree:
            case bridge:
            case river:
            case rock:
            case lava:
            case cooledlava:
            case swamp:
            case bramble:
            case pine:
            case snowtree:
            case iceblock:
                _passable = false;  break;
            case ground:
            case humus:
            case darkgrass:
            case sand:
            case snow:
            case grass:
                _passable = true;   break;
            default:
                break;
        }
        _neighbors = {};
    };
    ~LTile() {};
    bool operator== (const LTile tile) {
        return (tile._id == _id);
    }
    
};
#endif /* LTile_hpp */
