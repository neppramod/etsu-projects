#include "utility.h"

using namespace std;

Utility::Utility()
{
}

void Utility::saveFile(char *fileName, char *content)
{
        // Append, if the line was not in the file
        ofstream output_file(fileName, ios::app);

        if(output_file.is_open()) {
            output_file << content << endl;
        }
        output_file.close();
}
