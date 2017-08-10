//
//  FileManager.cpp
//  InfectYourCanard
//
//  Created by Remi DECELLE on 18/07/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#include "FileManager.h"

void FileManager::setFile(const std::string &file) {
    _file = file;
}

void FileManager::readMap(Model *model) {
    Map* map = new Map(NUMBER_WIDTH_TILES, NUMBER_HEIGHT_TILES);
    
    char *path = (char *)_file.c_str();
    FILE *stream;
    int istat = 0;
    int x,y;
    stream = std::fopen(path, "r");
    
    int chrono;
    int nbcanards=0;
    int c_amount, f_amount, ca_amount, b_amount;
    if(stream == nullptr)
        printf("Le fichier n'existe pas \n");
    else {
        fscanf(stream, "%d", &chrono);
        fscanf(stream, "%d", &nbcanards);
        fscanf(stream, "%d", &c_amount);
        fscanf(stream, "%d", &f_amount);
        fscanf(stream, "%d", &ca_amount);
        fscanf(stream, "%d", &b_amount);
        for( y=0; y<NUMBER_HEIGHT_TILES; y++) {
            for( x=0; x<NUMBER_WIDTH_TILES; x++) {
                int value;
                istat=fscanf(stream, "%d", &value);
                map->setTile(x, y, value);
                if(istat != 1)
                    break;
            }
            if(istat != 1)
                break;
        }
        
        // Ne pas oublier de fermer le stream
        fclose(stream);
    }
    model->setNumberOfDucks(nbcanards);
    model->setMap(map);
};

void FileManager::readMap(std::string file) {
    return;
};
