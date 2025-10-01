#ifndef INFO_H
#define INFO_H

#include <fstream>
#include <iostream>
#include <string>

constexpr int MAX_255INTENSITY_LIMIT = 255;
static constexpr int MAX_LEVEL_LIMIT = 65535;

struct Imagen {
    std::string formato;
    int altura                = 0;
    int anchura               = 0;
    mutable int maxIntensidad = 0;
};

Imagen save_info(std::ifstream & file_image);
int info(std::ifstream & fileImage);

#endif
