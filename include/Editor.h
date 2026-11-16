
#ifndef EDITOR_H
#define EDITOR_H

#include <string>
#include <vector>
#include "Document.h"
#include "UndoManager.h"
#include "SearchEngine.h"

using namespace std;

// Connects all parts of our text editor.
class Editor
{

private:
    Document document;
    UndoManager undoManager;

    string currentFilename;
    string lastError;

public:
    // Creates a new editor.
    Editor();

    // Returns the document for reading.
    const Document &getDocument() const;

    // Returns the last error message.
    string getLastError() const;

    // Returns the current filename.
    string getFilename() const;

    // Creates a new empty document.
    void newDocument();

    // Opens an existing text file.
    bool openFile(const string &filename);

    // Saves to the current filename.
    bool saveFile();

    // Saves using a new filename.
    bool saveFileAs(const string &filename);

    // Inserts text at a specified position.
    bool insertText(int line, int column,
                    const string &text);

    // Deletes a selected text range.
    bool deleteText(int startLine, int startColumn,
                    int endLine, int endColumn);

    // Searches for text.
    vector<Match> search(const string &text);

    // Replaces one occurrence.
    bool replaceOne(const string &oldText,
                    const string &newText,
                    int occurrence);

    // Replaces all occurrences.
    int replaceAll(const string &oldText,
                   const string &newText);

    // Undoes the latest editing command.
    bool undo();
};

#endif
