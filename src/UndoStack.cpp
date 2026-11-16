
#include "UndoStack.h"

// Creates an empty undo stack.
UndoStack::UndoStack()
{
    topNode = nullptr;
    totalRecords = 0;
}

// Releases memory when the stack is destroyed.
UndoStack::~UndoStack()
{
    clear();
}

// Pushes a record onto the top of the stack.
void UndoStack::push(UndoRecord record)
{

    StackNode *newNode = new StackNode;

    newNode->record = record;
    newNode->next = topNode;

    topNode = newNode;
    totalRecords++;
}

// Removes the latest record from the stack.
bool UndoStack::pop(UndoRecord &record)
{

    // An empty stack has nothing to remove.
    if (topNode == nullptr)
    {
        return false;
    }

    // Save the top node before deleting it.
    StackNode *oldTop = topNode;

    // Return the record to the caller.
    record = oldTop->record;

    // Move the top pointer to the next node.
    topNode = oldTop->next;

    delete oldTop;
    totalRecords--;

    return true;
}

// Returns true when no records are stored.
bool UndoStack::isEmpty() const
{
    return topNode == nullptr;
}

// Returns the current number of records.
int UndoStack::getSize() const
{
    return totalRecords;
}

// Deletes every node from the stack.
void UndoStack::clear()
{

    while (topNode != nullptr)
    {
        StackNode *oldTop = topNode;
        topNode = topNode->next;
        delete oldTop;
    }

    totalRecords = 0;
}
