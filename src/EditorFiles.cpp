
#include "Editor.h"
#include "FileManager.h"

using namespace std;

// Creates a new empty document.
void Editor::newDocument()
{

    document.clear();
    undoManager.clearHistory();

    currentFilename = "";
    lastError = "";
}

// Opens a file and loads it into the document.
bool Editor::openFile(const string &filename)
{

    lastError = "";

    bool success = FileManager::load(
        filename, document, lastError);

    if (success == false)
    {
        return false;
    }

    // Old undo records no longer apply.
    undoManager.clearHistory();

    currentFilename = filename;
    return true;
}

// Saves using the existing filename.
bool Editor::saveFile()
{

    lastError = "";

    if (currentFilename.empty())
    {
        lastError = "No filename. Use Save As first.";
        return false;
    }

    return FileManager::save(
        currentFilename, document, lastError);
}

// Saves the document under a new filename.
bool Editor::saveFileAs(const string &filename)
{

    lastError = "";

    bool success = FileManager::save(
        filename, document, lastError);

    if (success == false)
    {
        return false;
    }

    currentFilename = filename;
    return true;
}
