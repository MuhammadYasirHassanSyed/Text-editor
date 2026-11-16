
#include <iostream>
#include "Document.h"
#include "UndoManager.h"
#include "ReplaceEngine.h"

using namespace std;

// Tests Replace One, Replace All and Undo.
int main()
{

    Document doc;
    UndoManager undoManager;
    string error;

    // Create a document with repeated words.
    doc.insertText(0, 0, "CAT AND CAT");
    doc.insertLine(1, "MY CAT IS HAPPY");

    cout << "ORIGINAL DOCUMENT" << endl;
    doc.display();

    // TEST 1: Replace the second CAT.
    bool success = ReplaceEngine::replaceOne(
        doc, undoManager, "CAT", "DOG", 2);

    cout << "\nAFTER REPLACE ONE" << endl;

    if (success)
    {
        doc.display();
    }

    // TEST 2: Undo the selected replacement.
    undoManager.undo(doc, error);

    cout << "\nAFTER UNDO REPLACE ONE" << endl;
    doc.display();

    // TEST 3: Replace all occurrences.
    int count = ReplaceEngine::replaceAll(
        doc, undoManager, "CAT", "DOG");

    cout << "\nAFTER REPLACE ALL" << endl;
    doc.display();

    cout << "Replacements made: " << count << endl;

    // TEST 4: Undo the entire Replace All operation.
    undoManager.undo(doc, error);

    cout << "\nAFTER UNDO REPLACE ALL" << endl;
    doc.display();

    // TEST 5: Search text does not exist.
    count = ReplaceEngine::replaceAll(
        doc, undoManager, "XYZ", "ABC");

    cout << "\nMissing word replacements: "
         << count << endl;

    // TEST 6: Empty search string.
    count = ReplaceEngine::replaceAll(
        doc, undoManager, "", "ABC");

    cout << "Empty search replacements: "
         << count << endl;

    // TEST 7: Invalid occurrence number.
    success = ReplaceEngine::replaceOne(
        doc, undoManager, "CAT", "DOG", 100);

    cout << "Invalid occurrence handled: "
         << (success ? "No" : "Yes") << endl;

    cout << "Final history count: "
         << undoManager.getHistoryCount() << endl;

    return 0;
}
