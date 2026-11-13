
#include <iostream>
#include "Document.h"

using namespace std;

// Tests retrieving text ranges for Undo.
int main()
{

    Document doc;

    doc.insertText(0, 0, "HELLO BEAUTIFUL WORLD");
    doc.insertLine(1, "DATA STRUCTURES");
    doc.insertLine(2, "GOODBYE");

    cout << "Original document:" << endl;
    doc.display();

    string result;

    // Retrieve BEAUTIFUL from line 1.
    if (doc.getTextRange(0, 6, 0, 15, result))
    {
        cout << "\nSelected word: " << result << endl;
    }

    // Retrieve text spanning three lines.
    if (doc.getTextRange(0, 16, 2, 4, result))
    {
        cout << "\nMultiline selection:" << endl;
        cout << result << endl;
    }

    // Test an invalid line.
    if (doc.getTextRange(0, 0, 100, 0, result) == false)
    {
        cout << "\nInvalid line handled!" << endl;
    }

    // Test reversed positions.
    if (doc.getTextRange(0, 10, 0, 2, result) == false)
    {
        cout << "Reversed range handled!" << endl;
    }

    cout << "\nDocument after all tests:" << endl;
    doc.display();

    return 0;
}
