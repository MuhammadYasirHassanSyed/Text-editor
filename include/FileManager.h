
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include "Document.h"

using namespace std;

// Handles opening and saving text files.
class FileManager
{

public:
    // Opens a file and loads its text into the document.
    static bool load(const string &filename,
                     Document &document,
                     string &error);

    // Saves the document into a text file.
    static bool save(const string &filename,
                     const Document &document,
                     string &error);
};

#endif
