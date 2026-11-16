
#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <string>
#include <vector>
#include "Document.h"
#include "EditorTypes.h"

using namespace std;

// Searches for text inside a document.
class SearchEngine
{

public:
    // Finds every occurrence of a search string.
    static vector<Match> findAll(
        const Document &document,
        const string &searchText);

    // Displays all matching line and column positions.
    static void displayMatches(
        const vector<Match> &matches);
};

#endif
