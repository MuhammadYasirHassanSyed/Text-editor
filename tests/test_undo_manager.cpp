
#include <iostream>
#include "Document.h"
#include "UndoManager.h"

using namespace std;

// Tests insertion, deletion, replacement and Undo.
int main()
{

    Document doc;
    UndoManager undoManager;
    string removedText;
    string error;

    // Create the starting document.
    doc.insertText(0, 0, "HELLO WORLD");

    cout << "ORIGINAL DOCUMENT" << endl;
    doc.display();

    // TEST 1: Insert text and save its undo record.
    if (doc.replaceTextRange(0, 5, 0, 5,
                             " BIG", removedText))
    {

        UndoRecord record;
        record.operationType = 1;
        record.line = 0;
        record.column = 5;
        record.removedText = removedText;
        record.insertedText = " BIG";

        undoManager.recordAction(record);
    }

    cout << "\nAFTER INSERTION" << endl;
    doc.display();

    // TEST 2: Delete text and record the change.
    if (doc.replaceTextRange(0, 6, 0, 10,
                             "", removedText))
    {

        UndoRecord record;
        record.operationType = 2;
        record.line = 0;
        record.column = 6;
        record.removedText = removedText;
        record.insertedText = "";

        undoManager.recordAction(record);
    }

    cout << "\nAFTER DELETION" << endl;
    doc.display();

    // TEST 3: Replace text and save the old value.
    if (doc.replaceTextRange(0, 6, 0, 11,
                             "C++", removedText))
    {

        UndoRecord record;
        record.operationType = 3;
        record.line = 0;
        record.column = 6;
        record.removedText = removedText;
        record.insertedText = "C++";

        undoManager.recordAction(record);
    }

    cout << "\nAFTER REPLACEMENT" << endl;
    doc.display();

    cout << "\nHISTORY COUNT: "
         << undoManager.getHistoryCount() << endl;

    // Undo the replacement.
    if (undoManager.undo(doc, error))
    {
        cout << "\nUNDO 1 - REPLACEMENT" << endl;
        doc.display();
    }

    // Undo the deletion.
    if (undoManager.undo(doc, error))
    {
        cout << "\nUNDO 2 - DELETION" << endl;
        doc.display();
    }

    // Undo the insertion.
    if (undoManager.undo(doc, error))
    {
        cout << "\nUNDO 3 - INSERTION" << endl;
        doc.display();
    }

    // TEST 4: Try undoing with an empty stack.
    if (undoManager.undo(doc, error) == false)
    {
        cout << "\nERROR: " << error << endl;
    }

    cout << "FINAL HISTORY COUNT: "
         << undoManager.getHistoryCount() << endl;

    return 0;
}
