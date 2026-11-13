
#ifndef LINE_BUFFER_H
#define LINE_BUFFER_H

#include <string>
using namespace std;

class LineBuffer
{

private:
    char *data;
    int length;
    int capacity;

    // Makes the array bigger when needed.
    void resize(int newCapacity);

public:
    // Creates an empty buffer.
    LineBuffer();

    // Creates a buffer with text.
    LineBuffer(const string &text);

    // Releases allocated memory.
    ~LineBuffer();

    // Returns the number of characters.
    int getLength() const;

    // Returns the stored text.
    string getText() const;

    // Inserts text at a given position.
    bool insertText(int position, const string &text);

    // Deletes characters from a position.
    bool deleteText(int position, int count);
};

#endif
