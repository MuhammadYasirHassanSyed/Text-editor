
#include <iostream>
#include <string>
#include "Document.h"

using namespace std;

int passed = 0;
int failed = 0;

// Displays whether a test passed or failed.
void check(bool condition, string testName)
{
    if (condition)
    {
        cout << "[PASS] " << testName << endl;
        passed++;
    }
    else
    {
        cout << "[FAIL] " << testName << endl;
        failed++;
    }
}

// Tests the document's boundary cases.
int main()
{

    Document doc;
    string text;
    string removedText;

    cout << "DOCUMENT BOUNDARY TESTS\n"
         << endl;

    // Test 1: Empty document.
    check(doc.isEmpty(), "Empty document");

    // Test 2: Initial line count.
    check(doc.getLineCount() == 1,
          "Initial line count");

    // Test 3: Insert at beginning.
    check(doc.insertText(0, 0, "HELLO"),
          "Insert at beginning");

    // Test 4: Insert at end.
    check(doc.insertText(0, 5, " WORLD"),
          "Insert at end");

    doc.getLine(0, text);
    check(text == "HELLO WORLD",
          "Verify inserted text");

    // Test 5: Negative line number.
    check(doc.insertText(-1, 0, "ABC") == false,
          "Negative line number");

    // Test 6: Invalid column.
    check(doc.insertText(0, 100, "ABC") == false,
          "Invalid column");

    // Test 7: Invalid deletion length.
    check(doc.deleteText(0, 0, 100) == false,
          "Invalid character deletion");

    // Test 8: Insert last line.
    check(doc.insertLine(1, "SECOND LINE"),
          "Insert last line");

    // Test 9: Insert first line.
    check(doc.insertLine(0, "FIRST LINE"),
          "Insert first line");

    // Test 10: Delete first line.
    check(doc.deleteLine(0),
          "Delete first line");

    // Test 11: Delete last line.
    check(doc.deleteLine(1),
          "Delete last line");

    // Test 12: Retrieve text for Undo.
    check(doc.getTextRange(0, 6, 0, 11, text) && text == "WORLD",
          "Extract text for Undo");

    // Test 13: Replace text.
    check(doc.replaceTextRange(
              0, 6, 0, 11, "C++", removedText) &&
              removedText == "WORLD",
          "Replace and save original text");

    // Test 14: Delete all remaining lines.
    check(doc.deleteLines(0, doc.getLineCount()),
          "Delete all lines");

    check(doc.isEmpty() && doc.getLineCount() == 1,
          "Document remains valid after deletion");

    // Test 15: Insert a long line.
    string longText = "";

    for (int i = 0; i < 10000; i++)
    {
        longText += 'A';
    }

    check(doc.insertText(0, 0, longText),
          "Insert 10000 characters");

    doc.getLine(0, text);

    check(text == longText,
          "Verify long line contents");

    // Test 16: Invalid multiline range.
    check(doc.deleteTextRange(
              0, 0, 100, 0) == false,
          "Invalid multiline deletion");

    // Test 17: Split a long line.
    check(doc.insertNewLine(0, 5000),
          "Split long line");

    check(doc.getLineCount() == 2,
          "Verify line count after split");

    // Test 18: Join lines.
    check(doc.deleteTextRange(
              0, 5000, 1, 0),
          "Join lines");

    doc.getLine(0, text);

    check(text == longText &&
              doc.getLineCount() == 1,
          "Verify restored long line");

    cout << "\n------------------------" << endl;
    cout << "Passed: " << passed << endl;
    cout << "Failed: " << failed << endl;
    cout << "------------------------" << endl;

    return failed == 0 ? 0 : 1;
}
