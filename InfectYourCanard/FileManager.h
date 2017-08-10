//
//  FileManager.h
//  InfectYourCanard
//
//  Created by Remi DECELLE on 18/07/2017.
//  Copyright © 2017 Remi DECELLE. All rights reserved.
//

#ifndef FileManager_h
#define FileManager_h

#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <fstream>
#include "Model.h"

class FileManager {
private:
    std::string _file;
    
public:
    FileManager() {_file = "";};
    FileManager(const std::string &file) {setFile(file);};
    
    // Actions
    void setFile(const std::string &file);
    void readMap(Model* model);
    void readMap(std::string file);
    void saveScores(std::vector<int> scores);
};

#endif /* FileManager_h */
