#include "Document.h"
#include <iostream>

using namespace std;

// Creates a document containing one empty line.
Document::Document()
{
    head = new LineNode("");
    tail = head;
    totalLines = 1;
}

// Frees all nodes when the document is destroyed.
Document::~Document()
{
    LineNode *current = head;

    while (current != nullptr)
    {
        LineNode *nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

// Finds a line node using its index.
LineNode *Document::getNode(int lineNumber) const
{
    if (lineNumber < 0 || lineNumber >= totalLines)
    {
        return nullptr;
    }

    LineNode *current = head;

    for (int i = 0; i < lineNumber; i++)
    {
        current = current->next;
    }

    return current;
}

// Removes all lines and creates one empty line.
void Document::clear()
{
    LineNode *current = head;

    while (current != nullptr)
    {
        LineNode *nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = new LineNode("");
    tail = head;
    totalLines = 1;
}

// Returns the total number of lines.
int Document::getLineCount() const
{
    return totalLines;
}

// Counts all characters without counting newline separators.
int Document::getCharacterCount() const
{
    int count = 0;
    LineNode *current = head;

    while (current != nullptr)
    {
        count += current->text.getLength();
        current = current->next;
    }

    return count;
}

// Checks whether the document has no text.
bool Document::isEmpty() const
{
    return totalLines == 1 && head->text.getLength() == 0;
}

// Copies one line's text into output.
bool Document::getLine(int lineNumber, string &output) const
{
    LineNode *node = getNode(lineNumber);

    if (node == nullptr)
    {
        return false;
    }

    output = node->text.getText();
    return true;
}

// Inserts a new line before the requested index.
bool Document::insertLine(int lineNumber, const string &text)
{
    if (lineNumber < 0 || lineNumber > totalLines)
    {
        return false;
    }

    LineNode *newNode = new LineNode(text);

    // Case 1: Insert at the beginning.
    if (lineNumber == 0)
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    // Case 2: Insert at the end.
    else if (lineNumber == totalLines)
    {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }

    // Case 3: Insert between two existing nodes.
    else
    {
        LineNode *current = getNode(lineNumber);
        LineNode *previous = current->prev;

        newNode->next = current;
        newNode->prev = previous;

        previous->next = newNode;
        current->prev = newNode;
    }

    totalLines++;
    return true;
}

// Deletes the line at the requested index.
bool Document::deleteLine(int lineNumber)
{
    LineNode *node = getNode(lineNumber);

    if (node == nullptr)
    {
        return false;
    }

    // Keep one empty line if only one line remains.
    if (totalLines == 1)
    {
        node->text.deleteText(0, node->text.getLength());
        return true;
    }

    // Update the previous node, or move head.
    if (node->prev != nullptr)
    {
        node->prev->next = node->next;
    }
    else
    {
        head = node->next;
    }

    // Update the next node, or move tail.
    if (node->next != nullptr)
    {
        node->next->prev = node->prev;
    }
    else
    {
        tail = node->prev;
    }

    delete node;
    totalLines--;

    return true;
}

// Displays every line with a visible line number.
void Document::display() const
{
    LineNode *current = head;
    int lineNumber = 1;

    cout << "\n----- DOCUMENT -----" << endl;

    while (current != nullptr)
    {
        cout << lineNumber << ": "
             << current->text.getText() << endl;

        current = current->next;
        lineNumber++;
    }

    cout << "--------------------" << endl;
}

// Inserts text at a specified line and column.
bool Document::insertText(int lineNumber,
                          int column,
                          const string &text)
{

    // Find the requested line.
    LineNode *current = getNode(lineNumber);

    // Check whether the line exists.
    if (current == nullptr)
    {
        return false;
    }

    // Insert using our custom dynamic array.
    return current->text.insertText(column, text);
}

// Deletes characters from a specified line.
bool Document::deleteText(int lineNumber,
                          int column,
                          int count)
{

    // Find the requested line.
    LineNode *current = getNode(lineNumber);

    // Check whether the line exists.
    if (current == nullptr)
    {
        return false;
    }

    // Delete using our custom dynamic array.
    return current->text.deleteText(column, count);
}

// Deletes multiple consecutive lines from the document.
bool Document::deleteLines(int startLine, int count)
{

    // Check invalid line numbers and counts.
    if (startLine < 0 || count <= 0 ||
        startLine >= totalLines)
    {
        return false;
    }

    // Check whether the requested range fits.
    if (count > totalLines - startLine)
    {
        return false;
    }

    // Remove one line at a time.
    for (int i = 0; i < count; i++)
    {
        deleteLine(startLine);
    }

    return true;
}

// Checks whether a character belongs to a word.
static bool isWordCharacter(char character)
{

    if (character >= 'A' && character <= 'Z')
    {
        return true;
    }

    if (character >= 'a' && character <= 'z')
    {
        return true;
    }

    if (character >= '0' && character <= '9')
    {
        return true;
    }

    if (character == '_')
    {
        return true;
    }

    return false;
}

// Deletes the whole word containing the selected column.
bool Document::deleteWord(int lineNumber, int column)
{

    string text;

    // Get the line; reject invalid line numbers.
    if (getLine(lineNumber, text) == false)
    {
        return false;
    }

    int length = (int)text.length();

    // Check that column points to a real character.
    if (column < 0 || column >= length)
    {
        return false;
    }

    // Spaces and punctuation are not words.
    if (isWordCharacter(text[column]) == false)
    {
        return false;
    }

    int start = column;
    int end = column + 1;

    // Find the beginning of the word.
    while (start > 0 &&
           isWordCharacter(text[start - 1]))
    {
        start--;
    }

    // Find the end of the word.
    while (end < length &&
           isWordCharacter(text[end]))
    {
        end++;
    }

    // Reuse our dynamic array deletion function.
    return deleteText(lineNumber, start, end - start);
}

// Deletes a range of characters in one line.
bool Document::deleteRange(int lineNumber,
                           int startColumn,
                           int endColumn)
{

    // The ending position must be after the start.
    if (startColumn < 0 || endColumn <= startColumn)
    {
        return false;
    }

    int count = endColumn - startColumn;

    // Existing deleteText checks the line and bounds.
    return deleteText(lineNumber, startColumn, count);
}

// Splits an existing line into two lines.

// Splits an existing line into two lines.
bool Document::insertNewLine(int lineNumber, int column)
{

    // Find the line we want to split.
    LineNode *current = getNode(lineNumber);

    if (current == nullptr)
    {
        return false;
    }

    int length = current->text.getLength();

    if (column < 0 || column > length)
    {
        return false;
    }

    string originalText = current->text.getText();

    string remainingText = originalText.substr(column);

    if (insertLine(lineNumber + 1, remainingText) == false)
    {
        return false;
    }

    current->text.deleteText(column, length - column);

    return true;
}

// Deletes text between two positions, joining lines if needed.
bool Document::deleteTextRange(int startLine,
                               int startColumn,
                               int endLine,
                               int endColumn)
{

    string firstText;
    string lastText;

    // Check whether both lines exist.
    if (getLine(startLine, firstText) == false ||
        getLine(endLine, lastText) == false)
    {
        return false;
    }

    if (startColumn < 0 ||
        endColumn < 0 ||
        startColumn > (int)firstText.length() ||
        endColumn > (int)lastText.length())
    {
        return false;
    }

    // The ending line cannot be before the starting line.
    if (endLine < startLine)
    {
        return false;
    }

    // Case 1: Both positions are on the same line.
    if (startLine == endLine)
    {

        if (endColumn < startColumn)
        {
            return false;
        }

        return deleteText(startLine,
                          startColumn,
                          endColumn - startColumn);
    }

    // Case 2: The range covers multiple lines.

    // Save the text after the ending position.
    string remainingText = lastText.substr(endColumn);

    // Remove everything after the starting position.
    int charactersToDelete =
        (int)firstText.length() - startColumn;

    deleteText(startLine, startColumn, charactersToDelete);

    // Attach the saved text to the first line.
    insertText(startLine, startColumn, remainingText);

    // Delete all other lines in the selected range.
    int linesToDelete = endLine - startLine;

    deleteLines(startLine + 1, linesToDelete);

    return true;
}

// Retrieves text between two positions without deleting it.
bool Document::getTextRange(int startLine,
                            int startColumn,
                            int endLine,
                            int endColumn,
                            string &result) const
{

    string firstText;
    string lastText;

    if (getLine(startLine, firstText) == false ||
        getLine(endLine, lastText) == false)
    {
        return false;
    }

    if (startColumn < 0 || endColumn < 0 ||
        startColumn > (int)firstText.length() ||
        endColumn > (int)lastText.length())
    {
        return false;
    }

    if (endLine < startLine)
    {
        return false;
    }

    if (startLine == endLine &&
        endColumn < startColumn)
    {
        return false;
    }

    string selectedText = "";

    // Case 1: Both positions are on the same line.
    if (startLine == endLine)
    {
        selectedText = firstText.substr(
            startColumn, endColumn - startColumn);

        result = selectedText;
        return true;
    }

    // Case 2: The range covers multiple lines.

    // Get text after the starting column.
    selectedText = firstText.substr(startColumn);

    // Copy the complete lines in between.
    for (int i = startLine + 1; i < endLine; i++)
    {
        string middleText;
        getLine(i, middleText);

        selectedText += "\n";
        selectedText += middleText;
    }

    // Add the selected part of the final line.
    selectedText += "\n";
    selectedText += lastText.substr(0, endColumn);

    result = selectedText;
    return true;
}
