
#include "Editor.h"
#include "ReplaceEngine.h"

using namespace std;

// Creates an editor with no filename.
Editor::Editor()
{
    currentFilename = "";
    lastError = "";
}

// Returns the document without allowing direct editing.
const Document &Editor::getDocument() const
{
    return document;
}

// Returns the last error message.
string Editor::getLastError() const
{
    return lastError;
}

// Returns the current filename.
string Editor::getFilename() const
{
    return currentFilename;
}

// Inserts text and saves an undo record.
bool Editor::insertText(int line, int column,
                        const string &text)
{

    lastError = "";

    if (text.empty())
    {
        lastError = "Cannot insert empty text.";
        return false;
    }

    string removedText;

    // Equal positions mean insertion without deletion.
    bool success = document.replaceTextRange(
        line, column, line, column,
        text, removedText);

    if (success == false)
    {
        lastError = "Invalid insertion position.";
        return false;
    }

    UndoRecord record;

    record.operationType = 1;
    record.line = line;
    record.column = column;
    record.removedText = removedText;
    record.insertedText = text;

    undoManager.recordAction(record);

    return true;
}

// Deletes text and saves it for Undo.
bool Editor::deleteText(int startLine, int startColumn,
                        int endLine, int endColumn)
{

    lastError = "";

    // Reject an empty selection.
    if (startLine == endLine &&
        startColumn == endColumn)
    {
        lastError = "No text selected.";
        return false;
    }

    string removedText;

    bool success = document.replaceTextRange(
        startLine, startColumn,
        endLine, endColumn,
        "", removedText);

    if (success == false)
    {
        lastError = "Invalid deletion range.";
        return false;
    }

    UndoRecord record;

    record.operationType = 2;
    record.line = startLine;
    record.column = startColumn;
    record.removedText = removedText;
    record.insertedText = "";

    undoManager.recordAction(record);

    return true;
}

// Searches for all occurrences of a string.
vector<Match> Editor::search(const string &text)
{

    lastError = "";

    if (text.empty())
    {
        lastError = "Search string cannot be empty.";
        return vector<Match>();
    }

    return SearchEngine::findAll(document, text);
}

// Replaces one occurrence and records Undo.
bool Editor::replaceOne(const string &oldText,
                        const string &newText,
                        int occurrence)
{

    lastError = "";

    if (oldText.empty())
    {
        lastError = "Search string cannot be empty.";
        return false;
    }

    bool success = ReplaceEngine::replaceOne(
        document, undoManager,
        oldText, newText, occurrence);

    if (success == false)
    {
        lastError = "Occurrence not found or invalid.";
    }

    return success;
}

// Replaces all non-overlapping occurrences.
int Editor::replaceAll(const string &oldText,
                       const string &newText)
{

    lastError = "";

    if (oldText.empty())
    {
        lastError = "Search string cannot be empty.";
        return 0;
    }

    int count = ReplaceEngine::replaceAll(
        document, undoManager,
        oldText, newText);

    if (count == 0)
    {
        lastError = "No matches replaced.";
    }

    return count;
}

// Reverses the latest editing operation.
bool Editor::undo()
{

    lastError = "";

    return undoManager.undo(document, lastError);
}
