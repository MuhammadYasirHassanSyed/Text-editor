
#include "SearchEngine.h"
#include <iostream>

using namespace std;

// Finds all occurrences of a search string.
vector<Match> SearchEngine::findAll(
    const Document &document,
    const string &searchText)
{

    vector<Match> matches;

    // An empty search string is invalid.
    if (searchText.empty())
    {
        return matches;
    }

    int searchLength = (int)searchText.length();

    // Search every line in the document.
    for (int lineNumber = 0;
         lineNumber < document.getLineCount();
         lineNumber++)
    {

        string line;

        // Read the current line.
        if (document.getLine(lineNumber, line) == false)
        {
            continue;
        }

        int lineLength = (int)line.length();

        // Try every possible starting position.
        for (int column = 0;
             column <= lineLength - searchLength;
             column++)
        {

            bool found = true;

            // Compare search characters one by one.
            for (int i = 0; i < searchLength; i++)
            {

                if (line[column + i] != searchText[i])
                {
                    found = false;
                    break;
                }
            }

            // Save the position when all characters match.
            if (found)
            {
                Match result;

                result.start.line = lineNumber;
                result.start.column = column;
                result.length = searchLength;

                matches.push_back(result);
            }
        }
    }

    return matches;
}

// Displays all matches using one-based numbering.
void SearchEngine::displayMatches(
    const vector<Match> &matches)
{

    if (matches.empty())
    {
        cout << "No matches found." << endl;
        return;
    }

    cout << "Total matches: " << matches.size() << endl;

    for (int i = 0; i < (int)matches.size(); i++)
    {

        cout << "Match " << i + 1
             << ": Line " << matches[i].start.line + 1
             << ", Column " << matches[i].start.column + 1
             << endl;
    }
}
