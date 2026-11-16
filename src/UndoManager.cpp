
#include "UndoManager.h"

// Creates an UndoManager with an empty history.
UndoManager::UndoManager()
{
    // The UndoStack constructor initializes the stack.
}

// Saves an editing operation in the stack.
void UndoManager::recordAction(const UndoRecord &record)
{
    history.push(record);
}

// Reverses the latest editing operation.
bool UndoManager::undo(Document &document, string &error)
{

    error = "";

    UndoRecord record;

    // Check whether there is an operation to undo.
    if (history.pop(record) == false)
    {
        error = "Nothing to undo.";
        return false;
    }

    // The recorded starting position.
    int startLine = record.line;
    int startColumn = record.column;

    // Initially, the end is equal to the start.
    int endLine = startLine;
    int endColumn = startColumn;

    // Find where the inserted text ends.
    for (int i = 0;
         i < (int)record.insertedText.length();
         i++)
    {

        if (record.insertedText[i] == '\n')
        {
            endLine++;
            endColumn = 0;
        }
        else
        {
            endColumn++;
        }
    }

    string removedDuringUndo;

    // Remove the inserted text and restore the old text.
    bool success = document.replaceTextRange(
        startLine,
        startColumn,
        endLine,
        endColumn,
        record.removedText,
        removedDuringUndo);

    // Restore the record if Undo could not complete.
    if (success == false)
    {
        history.push(record);
        error = "Undo failed: document positions are invalid.";
        return false;
    }

    return true;
}

// Returns true if the history contains an operation.
bool UndoManager::canUndo() const
{
    return history.isEmpty() == false;
}

// Returns the number of stored editing operations.
int UndoManager::getHistoryCount() const
{
    return history.getSize();
}

// Removes all saved editing operations.
void UndoManager::clearHistory()
{
    history.clear();
}
