
#include "Menu.h"
#include "SearchEngine.h"
#include <iostream>

using namespace std;

// Inserts text at a selected line and column.
void Menu::insertText()
{
    int line, column;
    string text;

    if (!readNumber("Line number: ", line))
        return;
    if (!readNumber("Column number: ", column))
        return;
    if (!readText("Text to insert: ", text))
        return;

    // Convert user input to zero-based indexing.
    if (line < 1 || column < 1)
    {
        cout << "Invalid position.\n";
        return;
    }

    if (editor.insertText(line - 1, column - 1, text))
        cout << "Text inserted successfully.\n";
    else
        showError();
}

// Deletes text between two positions.
void Menu::deleteText()
{
    int startLine, startColumn;
    int endLine, endColumn;

    if (!readNumber("Start line: ", startLine))
        return;
    if (!readNumber("Start column: ", startColumn))
        return;
    if (!readNumber("End line: ", endLine))
        return;
    if (!readNumber("End column: ", endColumn))
        return;

    if (startLine < 1 || startColumn < 1 ||
        endLine < 1 || endColumn < 1)
    {
        cout << "Invalid position.\n";
        return;
    }

    if (editor.deleteText(startLine - 1, startColumn - 1,
                          endLine - 1, endColumn - 1))
        cout << "Text deleted successfully.\n";
    else
        showError();
}

// Searches the document for a string.
void Menu::searchText()
{
    string text;

    if (!readText("Enter search text: ", text))
        return;

    vector<Match> matches = editor.search(text);

    if (!editor.getLastError().empty())
    {
        showError();
        return;
    }

    SearchEngine::displayMatches(matches);
}

// Replaces one selected occurrence.
void Menu::replaceOne()
{
    string oldText, newText;
    int occurrence;

    if (!readText("Search text: ", oldText))
        return;
    if (!readText("Replacement text: ", newText))
        return;
    if (!readNumber("Occurrence number: ", occurrence))
        return;

    if (editor.replaceOne(oldText, newText, occurrence))
        cout << "Occurrence replaced successfully.\n";
    else
        showError();
}

// Replaces all occurrences.
void Menu::replaceAll()
{
    string oldText, newText;

    if (!readText("Search text: ", oldText))
        return;
    if (!readText("Replacement text: ", newText))
        return;

    int count = editor.replaceAll(oldText, newText);

    if (count > 0)
        cout << "Replacements made: " << count << endl;
    else
        showError();
}

// Inserts a newline at the selected position.
void Menu::insertNewLine()
{
    int line, column;

    if (!readNumber("Line number: ", line))
        return;
    if (!readNumber("Column number: ", column))
        return;

    if (line < 1 || column < 1)
    {
        cout << "Invalid position.\n";
        return;
    }

    // A newline is represented by '\n'.
    if (editor.insertText(line - 1, column - 1, "\n"))
        cout << "New line inserted successfully.\n";
    else
        showError();
}
