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
    std::ifstream infile(_file);
    float chrono = 10.0f;
    int numDucks=100;
    if (infile.is_open()) {
        while (infile >> chrono >> numDucks)
            std::cout << chrono << " " << numDucks << "\n";
    }
    else
        std::cout << "Failed to open file : " << _file << std::endl;
    /*
    char *path = (char *)_file.c_str();
    FILE *stream;
    stream = std::fopen(path, "r");
    
    if(stream == nullptr)
        printf("Le fichier n'existe pas : %s \n", _file.c_str());
    else {
        fscanf(stream, "%f", &chrono);
        fscanf(stream, "%d", &nbcanards);
        // Ne pas oublier de fermer le stream
        fclose(stream);
    }*/
    model->setTimer(chrono);
    model->setNumberOfDucks(numDucks);
    model->setMap(map);
};

void FileManager::readMap(std::string file) {
    return;
};
