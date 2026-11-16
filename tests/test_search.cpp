
#include <iostream>
#include "Document.h"
#include "SearchEngine.h"

using namespace std;

// Tests our naive search algorithm.
int main()
{

    Document doc;

    // Create a document containing repeated words.
    doc.insertText(0, 0, "HELLO WORLD HELLO");
    doc.insertLine(1, "WORLD IS BEAUTIFUL");
    doc.insertLine(2, "HELLO AGAIN");

    cout << "SEARCH ENGINE TEST" << endl;

    cout << "\nOriginal document:" << endl;
    doc.display();

    // Test 1: Find HELLO.
    cout << "\nSearching for HELLO:" << endl;

    vector<Match> matches =
        SearchEngine::findAll(doc, "HELLO");

    SearchEngine::displayMatches(matches);

    // Test 2: Find WORLD.
    cout << "\nSearching for WORLD:" << endl;

    matches = SearchEngine::findAll(doc, "WORLD");
    SearchEngine::displayMatches(matches);

    // Test 3: Search for a missing word.
    cout << "\nSearching for XYZ:" << endl;

    matches = SearchEngine::findAll(doc, "XYZ");
    SearchEngine::displayMatches(matches);

    // Test 4: Empty search.
    cout << "\nSearching for an empty string:" << endl;

    matches = SearchEngine::findAll(doc, "");
    SearchEngine::displayMatches(matches);

    // Test 5: Overlapping matches.
    doc.clear();
    doc.insertText(0, 0, "BANANA");

    cout << "\nSearching for ANA in BANANA:" << endl;

    matches = SearchEngine::findAll(doc, "ANA");
    SearchEngine::displayMatches(matches);

    return 0;
}
