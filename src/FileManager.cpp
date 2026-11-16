
#include "FileManager.h"
#include <fstream>

using namespace std;

// Opens a text file and loads its lines into Document.
bool FileManager::load(const string &filename,
                       Document &document,
                       string &error)
{

    error = "";

    // A filename must not be empty.
    if (filename.empty())
    {
        error = "Filename cannot be empty.";
        return false;
    }

    ifstream file(filename.c_str());

    // Check whether the file opened successfully.
    if (!file.is_open())
    {
        error = "Could not open file: " + filename;
        return false;
    }

    // Create a temporary document to avoid losing
    // the current document if reading fails.
    Document temporaryDocument;
    string line;
    int lineNumber = 0;

    // Read the text file one line at a time.
    while (getline(file, line))
    {

        if (lineNumber == 0)
        {
            temporaryDocument.insertText(0, 0, line);
        }
        else
        {
            temporaryDocument.insertLine(lineNumber, line);
        }

        lineNumber++;
    }

    // Check whether a reading error occurred.
    if (file.bad())
    {
        error = "An error occurred while reading the file.";
        file.close();
        return false;
    }

    file.close();

    // Only replace the current document after
    // successfully reading the entire file.
    document.clear();

    for (int i = 0; i < temporaryDocument.getLineCount(); i++)
    {

        string text;
        temporaryDocument.getLine(i, text);

        if (i == 0)
        {
            document.insertText(0, 0, text);
        }
        else
        {
            document.insertLine(i, text);
        }
    }

    return true;
}

// Saves the current document to a text file.
bool FileManager::save(const string &filename,
                       const Document &document,
                       string &error)
{

    error = "";

    // Check that a filename was provided.
    if (filename.empty())
    {
        error = "Filename cannot be empty.";
        return false;
    }

    ofstream file(filename.c_str());

    // Check whether the file opened successfully.
    if (!file.is_open())
    {
        error = "Could not save file: " + filename;
        return false;
    }

    // Write every line from the linked list.
    for (int i = 0; i < document.getLineCount(); i++)
    {

        string text;
        document.getLine(i, text);

        file << text;

        // Add a newline between document lines.
        if (i < document.getLineCount() - 1)
        {
            file << '\n';
        }
    }

    // Check for errors while writing.
    if (!file.good())
    {
        error = "An error occurred while writing the file.";
        file.close();
        return false;
    }

    file.close();

    // Also check whether closing the file succeeded.
    if (file.fail())
    {
        error = "An error occurred while closing the file.";
        return false;
    }

    return true;
}
