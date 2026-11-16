
#include "ReplaceEngine.h"
#include "SearchEngine.h"
#include <vector>

using namespace std;

// Combines all document lines into one string.
static string getDocumentText(const Document &document)
{

    string allText = "";

    for (int i = 0; i < document.getLineCount(); i++)
    {

        string line;
        document.getLine(i, line);

        if (i > 0)
        {
            allText += "\n";
        }

        allText += line;
    }

    return allText;
}

// Replaces one selected occurrence of a string.
bool ReplaceEngine::replaceOne(
    Document &document,
    UndoManager &undoManager,
    const string &searchText,
    const string &newText,
    int occurrenceNumber)
{

    // Reject invalid input.
    if (searchText.empty() || occurrenceNumber <= 0)
    {
        return false;
    }

    // Find all matching positions.
    vector<Match> matches =
        SearchEngine::findAll(document, searchText);

    // Check whether the requested occurrence exists.
    if (occurrenceNumber > (int)matches.size())
    {
        return false;
    }

    // Convert occurrence number to zero-based index.
    Match selected = matches[occurrenceNumber - 1];

    int line = selected.start.line;
    int startColumn = selected.start.column;
    int endColumn = startColumn + selected.length;

    string removedText;

    // Perform the replacement.
    bool success = document.replaceTextRange(
        line,
        startColumn,
        line,
        endColumn,
        newText,
        removedText);

    if (success == false)
    {
        return false;
    }

    // Save the replacement for Undo.
    UndoRecord record;

    record.operationType = 3;
    record.line = line;
    record.column = startColumn;
    record.removedText = removedText;
    record.insertedText = newText;

    undoManager.recordAction(record);

    return true;
}

// Replaces every non-overlapping occurrence.
int ReplaceEngine::replaceAll(
    Document &document,
    UndoManager &undoManager,
    const string &searchText,
    const string &newText)
{

    // Empty search strings are not allowed.
    if (searchText.empty())
    {
        return 0;
    }

    // Find every matching position.
    vector<Match> matches =
        SearchEngine::findAll(document, searchText);

    if (matches.empty())
    {
        return 0;
    }

    // Save the complete original document for Undo.
    string originalText = getDocumentText(document);

    int originalLastLine = document.getLineCount() - 1;

    string lastLineText;
    document.getLine(originalLastLine, lastLineText);

    int originalLastColumn = (int)lastLineText.length();

    // Build the new document without overlapping replacements.
    string updatedText = "";
    int replacementCount = 0;
    int nextAllowedColumn = 0;

    // Process each line in document order.
    for (int lineNumber = 0;
         lineNumber < document.getLineCount();
         lineNumber++)
    {

        string line;
        document.getLine(lineNumber, line);

        string updatedLine = "";
        int copiedUntil = 0;
        nextAllowedColumn = 0;

        // Look through the matches for this line.
        for (int i = 0; i < (int)matches.size(); i++)
        {

            if (matches[i].start.line != lineNumber)
            {
                continue;
            }

            int column = matches[i].start.column;

            // Ignore matches overlapping an earlier replacement.
            if (column < nextAllowedColumn)
            {
                continue;
            }

            // Copy unchanged characters before this match.
            for (int j = copiedUntil; j < column; j++)
            {
                updatedLine += line[j];
            }

            // Add the replacement text.
            updatedLine += newText;

            copiedUntil = column + (int)searchText.length();
            nextAllowedColumn = copiedUntil;
            replacementCount++;
        }

        // Copy the remaining original characters.
        for (int j = copiedUntil; j < (int)line.length(); j++)
        {
            updatedLine += line[j];
        }

        if (lineNumber > 0)
        {
            updatedText += "\n";
        }

        updatedText += updatedLine;
    }

    // Replace the document as one editing operation.
    string removedText;

    bool success = document.replaceTextRange(
        0,
        0,
        originalLastLine,
        originalLastColumn,
        updatedText,
        removedText);

    if (success == false)
    {
        return 0;
    }

    // One record represents the complete Replace All command.
    UndoRecord record;

    record.operationType = 3;
    record.line = 0;
    record.column = 0;
    record.removedText = originalText;
    record.insertedText = updatedText;

    undoManager.recordAction(record);

    return replacementCount;
}
