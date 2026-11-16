
#include <iostream>
#include "Document.h"

using namespace std;

// Tests the public functions used by Person B.
int main()
{

    Document doc;
    string result;
    string removedText;

    cout << "DOCUMENT API TEST" << endl;

    // Test 1: Create a document.
    doc.insertText(0, 0, "HELLO WORLD");
    doc.insertLine(1, "DATA STRUCTURES");

    cout << "\n1. Original document:" << endl;
    doc.display();

    // Test 2: Search support through getLine().
    string line;

    if (doc.getLine(0, line))
    {
        cout << "\n2. First line: " << line << endl;
    }

    // Test 3: Retrieve text for Undo.
    if (doc.getTextRange(0, 6, 0, 11, result))
    {
        cout << "3. Selected text: " << result << endl;
    }

    // Test 4: Replace WORLD with C++.
    if (doc.replaceTextRange(0, 6, 0, 11,
                             "C++", removedText))
    {

        cout << "\n4. After replacement:" << endl;
        doc.display();

        cout << "Removed text: " << removedText << endl;
    }

    // Test 5: Simulate Undo.
    if (doc.replaceTextRange(0, 6, 0, 9,
                             removedText, result))
    {

        cout << "\n5. After simulated Undo:" << endl;
        doc.display();
    }

    // Test 6: Invalid position.
    if (doc.getLine(100, line) == false)
    {
        cout << "\n6. Invalid line handled!" << endl;
    }

    // Test 7: Verify statistics.
    cout << "\n7. Total lines: "
         << doc.getLineCount() << endl;

    cout << "Total characters: "
         << doc.getCharacterCount() << endl;

    return 0;
}
