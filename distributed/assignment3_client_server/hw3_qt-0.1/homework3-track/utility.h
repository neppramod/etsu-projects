#ifndef UTILITY_H
#define UTILITY_H

#include <fstream>
#include <iostream>
#include <string.h>
#include <string>

class Utility
{
public:
    Utility();
    void saveFile(char *fileName, char *content);
};

#endif // UTILITY_H
