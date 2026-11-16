
#ifndef REPLACE_ENGINE_H
#define REPLACE_ENGINE_H

#include <string>
#include "Document.h"
#include "UndoManager.h"

using namespace std;

// Handles replacing text in the document.
class ReplaceEngine
{

public:
    // Replaces one selected occurrence.
    static bool replaceOne(
        Document &document,
        UndoManager &undoManager,
        const string &searchText,
        const string &newText,
        int occurrenceNumber);

    // Replaces all non-overlapping occurrences.
    // Returns how many replacements were made.
    static int replaceAll(
        Document &document,
        UndoManager &undoManager,
        const string &searchText,
        const string &newText);
};

#endif
