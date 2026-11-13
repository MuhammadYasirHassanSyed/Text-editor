#ifndef EDITOR_TYPES_H
#define EDITOR_TYPES_H

// Stores the position of a character in the document.
struct Position
{
    int line;
    int column;
};

// Stores the location of a search match.
struct Match
{
    Position start;
    int length;
};

#endif
