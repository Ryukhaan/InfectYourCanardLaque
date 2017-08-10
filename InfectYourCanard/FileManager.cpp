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
    stream = std::fopen(path, "r");
    
    float chrono = 0.0f;
    int nbcanards=0;
    if(stream == nullptr)
        printf("Le fichier n'existe pas \n");
    else {
        fscanf(stream, "%f", &chrono);
        fscanf(stream, "%d", &nbcanards);
        // Ne pas oublier de fermer le stream
        fclose(stream);
    }
    model->setTimer(chrono);
    model->setNumberOfDucks(nbcanards);
    model->setMap(map);
};

void FileManager::readMap(std::string file) {
    return;
};
