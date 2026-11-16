
#include "Menu.h"
#include <iostream>
#include <sstream>

using namespace std;

// Reads a valid whole number.
bool Menu::readNumber(const string &message, int &number)
{
    string input;

    cout << message;

    if (!getline(cin, input))
    {
        return false;
    }

    stringstream stream(input);
    char extra;

    if (!(stream >> number) || (stream >> extra))
    {
        cout << "Invalid number. Please try again.\n";
        return false;
    }

    return true;
}

// Reads a complete line of text.
bool Menu::readText(const string &message, string &text)
{
    cout << message;
    return static_cast<bool>(getline(cin, text));
}

// Displays the last error message.
void Menu::showError()
{
    cout << "Error: " << editor.getLastError() << endl;
}

// Displays the complete text editor menu.
void Menu::displayMenu()
{
    cout << "\n================================\n";
    cout << "          TEXT EDITOR\n";
    cout << "================================\n";

    cout << " 1. New Document\n";
    cout << " 2. Open File\n";
    cout << " 3. Save File\n";
    cout << " 4. Save As\n";
    cout << " 5. Display Document\n";
    cout << " 6. Insert Text\n";
    cout << " 7. Delete Text Range\n";
    cout << " 8. Search Text\n";
    cout << " 9. Replace One\n";
    cout << "10. Replace All\n";
    cout << "11. Undo\n";
    cout << "12. Document Statistics\n";
    cout << "13. Insert New Line\n";
    cout << "14. Delete Word\n";
    cout << "15. Delete Line\n";
    cout << "16. Delete Multiple Lines\n";
    cout << " 0. Exit\n";

    cout << "================================\n";
}

// Runs the main menu.
void Menu::run()
{
    int choice;
    string filename;

    while (true)
    {
        displayMenu();

        if (!readNumber("Enter your choice: ", choice))
        {
            if (cin.eof())
            {
                break;
            }
            continue;
        }

        switch (choice)
        {

        case 1:
            editor.newDocument();
            cout << "New document created.\n";
            break;

        case 2:
            if (!readText("Enter filename: ", filename))
                return;

            if (editor.openFile(filename))
                cout << "File opened successfully.\n";
            else
                showError();
            break;

        case 3:
            if (editor.saveFile())
                cout << "File saved successfully.\n";
            else
                showError();
            break;

        case 4:
            if (!readText("Save as filename: ", filename))
                return;

            if (editor.saveFileAs(filename))
                cout << "File saved successfully.\n";
            else
                showError();
            break;

        case 5:
            editor.getDocument().display();
            break;

        case 6:
            insertText();
            break;

        case 7:
            deleteText();
            break;

        case 8:
            searchText();
            break;

        case 9:
            replaceOne();
            break;

        case 10:
            replaceAll();
            break;

        case 11:
            if (editor.undo())
                cout << "Undo successful.\n";
            else
                showError();
            break;

        case 12:
            cout << "Lines: "
                 << editor.getDocument().getLineCount()
                 << endl;

            cout << "Characters: "
                 << editor.getDocument().getCharacterCount()
                 << endl;
            break;

        case 13:
            insertNewLine();
            break;

        case 14:
            deleteWord();
            break;

        case 15:
            deleteLine();
            break;

        case 16:
            deleteMultipleLines();
            break;

        case 0:
            cout << "Exiting Text Editor.\n";
            return;

        default:
            cout << "Invalid menu choice.\n";
            break;
        }
    }
}
