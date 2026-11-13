#include "LineBuffer.h"

// Creates an empty buffer with space for 10 characters.
LineBuffer::LineBuffer()
{
    capacity = 10;
    length = 0;
    data = new char[capacity];
}

// Creates a buffer containing the given text.
LineBuffer::LineBuffer(const string &text)
{
    capacity = 10;

    while (capacity <= (int)text.length())
    {
        capacity = capacity * 2;
    }

    length = (int)text.length();
    data = new char[capacity];

    for (int i = 0; i < length; i++)
    {
        data[i] = text[i];
    }
}

// Deletes the dynamically allocated character array.
LineBuffer::~LineBuffer()
{
    delete[] data;
}

// Creates a larger array and copies existing characters.
void LineBuffer::resize(int newCapacity)
{
    char *newData = new char[newCapacity];

    for (int i = 0; i < length; i++)
    {
        newData[i] = data[i];
    }

    delete[] data;

    data = newData;
    capacity = newCapacity;
}

// Returns the number of characters in the line.
int LineBuffer::getLength() const
{
    return length;
}

// Converts our character array to a string.
string LineBuffer::getText() const
{
    string text = "";

    for (int i = 0; i < length; i++)
    {
        text += data[i];
    }

    return text;
}

// Inserts text at the specified character position.
bool LineBuffer::insertText(int position, const string &text)
{

    if (position < 0 || position > length)
    {
        return false;
    }

    int textLength = (int)text.length();

    // Increase capacity until the new text fits.
    while (length + textLength >= capacity)
    {
        resize(capacity * 2);
    }

    // Shift characters right to create space.
    for (int i = length - 1; i >= position; i--)
    {
        data[i + textLength] = data[i];
    }

    // Copy the new text into the empty space.
    for (int i = 0; i < textLength; i++)
    {
        data[position + i] = text[i];
    }

    length = length + textLength;
    return true;
}

// Deletes count characters starting at position.
bool LineBuffer::deleteText(int position, int count)
{

    if (position < 0 || count < 0 ||
        position > length || count > length - position)
    {
        return false;
    }

    // Shift the remaining characters left.
    for (int i = position; i < length - count; i++)
    {
        data[i] = data[i + count];
    }

    length = length - count;
    return true;
}
