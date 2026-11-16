
#include <iostream>
#include "UndoStack.h"

using namespace std;

// Tests our custom stack operations.
int main()
{

    UndoStack stack;

    cout << "UNDO STACK TEST" << endl;

    // Check the initial state.
    cout << "Initially empty: "
         << (stack.isEmpty() ? "Yes" : "No") << endl;

    // Create the first editing record.
    UndoRecord first;

    first.operationType = 1;
    first.line = 0;
    first.column = 0;
    first.removedText = "";
    first.insertedText = "HELLO";

    // Create the second editing record.
    UndoRecord second;

    second.operationType = 2;
    second.line = 0;
    second.column = 6;
    second.removedText = "WORLD";
    second.insertedText = "";

    // Add records to the stack.
    stack.push(first);
    stack.push(second);

    cout << "Size after pushes: "
         << stack.getSize() << endl;

    // Remove the latest record.
    UndoRecord result;

    if (stack.pop(result))
    {
        cout << "First pop: "
             << result.removedText << endl;
    }

    if (stack.pop(result))
    {
        cout << "Second pop: "
             << result.insertedText << endl;
    }

    // Test popping an empty stack.
    if (stack.pop(result) == false)
    {
        cout << "Empty stack handled!" << endl;
    }

    cout << "Final size: "
         << stack.getSize() << endl;

    // Verify the clear operation.
    stack.push(first);
    stack.clear();

    cout << "Empty after clear: "
         << (stack.isEmpty() ? "Yes" : "No") << endl;

    return 0;
}
