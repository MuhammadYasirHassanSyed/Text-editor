
#ifndef UNDO_STACK_H
#define UNDO_STACK_H

#include <string>
using namespace std;

// Stores information about one editing operation.
struct UndoRecord
{
    int operationType;
    int line;
    int column;

    string removedText;
    string insertedText;
};

// A node used by our custom linked-list stack.
struct StackNode
{
    UndoRecord record;
    StackNode *next;
};

// Stores editing history in LIFO order.
class UndoStack
{

private:
    StackNode *topNode;
    int totalRecords;

public:
    // Creates an empty stack.
    UndoStack();

    // Releases all stack nodes.
    ~UndoStack();

    // Adds a new record to the top.
    void push(UndoRecord record);

    // Removes the top record and returns it.
    bool pop(UndoRecord &record);

    // Checks whether the stack is empty.
    bool isEmpty() const;

    // Returns the number of records.
    int getSize() const;

    // Removes all records.
    void clear();

    // Prevent accidental copying of the stack.
    UndoStack(const UndoStack &) = delete;
    UndoStack &operator=(const UndoStack &) = delete;
};

#endif
