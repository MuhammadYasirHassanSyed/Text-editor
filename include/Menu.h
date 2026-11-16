#ifndef MENU_H
#define MENU_H

#include "Editor.h"
#include <string>

using namespace std;

class Menu
{

private:
    Editor editor;

    bool readNumber(const string &message, int &number);
    bool readText(const string &message, string &text);

    void showError();

    void insertText();
    void deleteText();
    void searchText();
    void replaceOne();
    void replaceAll();
    void insertNewLine();

    // Step 8: New deletion functions
    void deleteWord();
    void deleteLine();
    void deleteMultipleLines();

    void displayMenu();

public:
    void run();
};

#endif