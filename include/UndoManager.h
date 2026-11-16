
#ifndef UNDO_MANAGER_H
#define UNDO_MANAGER_H

#include <string>
#include "UndoStack.h"
#include "Document.h"

using namespace std;

// Manages the undo history of the text editor.
class UndoManager
{

private:
    UndoStack history;

public:
    // Creates an empty undo manager.
    UndoManager();

    // Saves a successful editing operation.
    void recordAction(const UndoRecord &record);

    // Reverses the most recent editing operation.
    bool undo(Document &document, string &error);

    // Checks whether Undo is available.
    bool canUndo() const;

    // Returns the number of saved operations.
    int getHistoryCount() const;

    // Removes all undo history.
    void clearHistory();
};

#endif
