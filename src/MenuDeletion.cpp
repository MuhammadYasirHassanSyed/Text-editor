
#include "Menu.h"
#include <iostream>

using namespace std;

static bool isWordCharacter(char c)
{
    return (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9') ||
           c == '_';
}

// Delete a word containing a selected character.
void Menu::deleteWord()
{
    int lineNumber, columnNumber;

    if (!readNumber("Line number: ", lineNumber))
        return;
    if (!readNumber("Column number: ", columnNumber))
        return;

    if (lineNumber < 1 || columnNumber < 1)
    {
        cout << "Invalid position.\n";
        return;
    }

    int line = lineNumber - 1;
    int column = columnNumber - 1;

    string text;

    if (!editor.getDocument().getLine(line, text))
    {
        cout << "Invalid line number.\n";
        return;
    }

    if (column >= (int)text.length() ||
        !isWordCharacter(text[column]))
    {
        cout << "Select a character inside a word.\n";
        return;
    }

    int start = column;
    int end = column + 1;

    while (start > 0 && isWordCharacter(text[start - 1]))
        start--;

    while (end < (int)text.length() &&
           isWordCharacter(text[end]))
        end++;

    if (editor.deleteText(line, start, line, end))
        cout << "Word deleted successfully.\n";
    else
        showError();
}

// Delete a complete line.
void Menu::deleteLine()
{
    int lineNumber;

    if (!readNumber("Line number to delete: ", lineNumber))
        return;

    int total = editor.getDocument().getLineCount();

    if (lineNumber < 1 || lineNumber > total)
    {
        cout << "Invalid line number.\n";
        return;
    }

    int line = lineNumber - 1;
    string text;

    editor.getDocument().getLine(line, text);

    bool success = false;

    if (total == 1)
    {
        if (text.empty())
        {
            cout << "Document is already empty.\n";
            return;
        }

        success = editor.deleteText(
            0, 0, 0, (int)text.length());
    }
    else if (line < total - 1)
    {
        success = editor.deleteText(
            line, 0, line + 1, 0);
    }
    else
    {
        string previous;
        editor.getDocument().getLine(line - 1, previous);

        success = editor.deleteText(
            line - 1, (int)previous.length(),
            line, (int)text.length());
    }

    if (success)
        cout << "Line deleted successfully.\n";
    else
        showError();
}

// Delete consecutive lines.
void Menu::deleteMultipleLines()
{
    int startLine, count;

    if (!readNumber("Starting line number: ", startLine))
        return;

    if (!readNumber("Number of lines to delete: ", count))
        return;

    int total = editor.getDocument().getLineCount();

    if (startLine < 1 || startLine > total ||
        count <= 0 || count > total - startLine + 1)
    {
        cout << "Invalid line range.\n";
        return;
    }

    int first = startLine - 1;
    int afterLast = first + count;

    bool success = false;

    if (afterLast < total)
    {
        success = editor.deleteText(
            first, 0, afterLast, 0);
    }
    else if (first == 0)
    {
        string lastText;

        editor.getDocument().getLine(
            total - 1, lastText);

        if (editor.getDocument().isEmpty())
        {
            cout << "Document is already empty.\n";
            return;
        }

        success = editor.deleteText(
            0, 0,
            total - 1, (int)lastText.length());
    }
    else
    {
        string previous, lastText;

        editor.getDocument().getLine(
            first - 1, previous);

        editor.getDocument().getLine(
            total - 1, lastText);

        success = editor.deleteText(
            first - 1, (int)previous.length(),
            total - 1, (int)lastText.length());
    }

    if (success)
        cout << "Selected lines deleted successfully.\n";
    else
        showError();
}
