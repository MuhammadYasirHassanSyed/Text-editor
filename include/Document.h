#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include "LineBuffer.h"
#include "EditorTypes.h"

using namespace std;

// Each node stores one line of the document.
struct LineNode
{
    LineBuffer text;
    LineNode *prev;
    LineNode *next;

    // Creates a node containing one line.
    LineNode(const string &lineText)
        : text(lineText)
    {
        prev = nullptr;
        next = nullptr;
    }
};

// Manages all lines using a doubly linked list.
class Document
{

private:
    LineNode *head;
    LineNode *tail;
    int totalLines;

    // Finds a node using its zero-based line number.
    LineNode *getNode(int lineNumber) const;

public:
    // Creates a document with one empty line.
    Document();

    // Frees all linked-list nodes.
    ~Document();

    // Removes all text and restores one empty line.
    void clear();

    // Returns the number of lines.
    int getLineCount() const;

    // Returns the total number of characters.
    int getCharacterCount() const;

    // Checks whether the document contains no text.
    bool isEmpty() const;

    // Gets one line's text.
    bool getLine(int lineNumber, string &output) const;

    // Inserts a new line before the given index.
    bool insertLine(int lineNumber, const string &text);

    // Deletes the line at the given index.
    bool deleteLine(int lineNumber);

    // Deletes multiple consecutive lines.
    bool deleteLines(int startLine, int count);

    // Inserts text inside an existing line.
    bool insertText(int lineNumber, int column, const string &text);

    // Deletes characters inside an existing line.
    bool deleteText(int lineNumber, int column, int count);

    // Deletes a word containing the selected character.
    bool deleteWord(int lineNumber, int column);

    // Deletes a character range within one line.
    // startColumn is included; endColumn is excluded.
    bool deleteRange(int lineNumber, int startColumn, int endColumn);

    // Splits a line at the given column.
    bool insertNewLine(int lineNumber, int column);

    // Deletes text between two positions.
    // Can delete across multiple lines.
    bool deleteTextRange(int startLine, int startColumn, int endLine, int endColumn);

    // Retrieves text between two positions.
    // Does not change the document.
    bool getTextRange(int startLine, int startColumn, int endLine, int endColumn, string &result) const;

    // Replaces a selected range and saves the removed text.
    bool replaceTextRange(int startLine, int startColumn, int endLine, int endColumn, const string &newText, string &removedText);

    // Displays all lines with their line numbers.
    void display() const;
};

#endif
