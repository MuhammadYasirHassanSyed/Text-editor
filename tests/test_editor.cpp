
#include <iostream>
#include "Editor.h"

using namespace std;

// Tests the Editor Controller.
int main()
{

    Editor editor;

    cout << "EDITOR CONTROLLER TEST" << endl;

    // Test 1: Insert text.
    editor.insertText(0, 0, "HELLO WORLD");

    cout << "\nAfter insertion:" << endl;
    editor.getDocument().display();

    // Test 2: Search for WORLD.
    vector<Match> matches = editor.search("WORLD");

    cout << "\nSearch results:" << endl;
    SearchEngine::displayMatches(matches);

    // Test 3: Replace WORLD with C++.
    editor.replaceOne("WORLD", "C++", 1);

    cout << "\nAfter replacement:" << endl;
    editor.getDocument().display();

    // Test 4: Undo replacement.
    editor.undo();

    cout << "\nAfter Undo:" << endl;
    editor.getDocument().display();

    // Test 5: Delete WORLD.
    editor.deleteText(0, 6, 0, 11);

    cout << "\nAfter deletion:" << endl;
    editor.getDocument().display();

    // Test 6: Undo deletion.
    editor.undo();

    cout << "\nAfter undoing deletion:" << endl;
    editor.getDocument().display();

    // Test 7: Save As.
    if (editor.saveFileAs("tests/editor_step6.txt"))
    {
        cout << "\nSave As successful!" << endl;
    }

    // Test 8: New Document.
    editor.newDocument();

    cout << "\nAfter New Document:" << endl;
    editor.getDocument().display();

    // Test 9: Open saved document.
    if (editor.openFile("tests/editor_step6.txt"))
    {
        cout << "\nAfter opening saved file:" << endl;
        editor.getDocument().display();
    }

    // Test 10: Invalid insertion.
    if (editor.insertText(100, 0, "TEST") == false)
    {
        cout << "\nError: "
             << editor.getLastError() << endl;
    }

    // Test 11: Invalid empty search.
    editor.search("");

    cout << "Error: "
         << editor.getLastError() << endl;

    return 0;
}
