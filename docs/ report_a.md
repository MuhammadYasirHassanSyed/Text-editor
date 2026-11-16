# CS-218 Data Structures and Algorithms

## Complex Engineering Problem: Design and Implementation of a Text Editor in C++

### Person A — Document Management and File Handling

## 1. Introduction

The objective of this project is to design and implement a basic text editor in C++ using fundamental data structures and algorithms.

The editor allows users to create, modify, display, open, and save text documents. The main focus is on efficient text representation and manipulation rather than developing a graphical user interface.

The project uses C++11 and follows a modular approach, with separate classes for document storage, character manipulation, and file handling.

## 2. Document Representation

The document is represented using a custom doubly linked list.

Each node represents one line of text and contains three components:

- A `LineBuffer` object to store characters.
- A `prev` pointer to the previous line.
- A `next` pointer to the next line.

The `Document` class maintains two pointers:

- `head` points to the first line.
- `tail` points to the last line.

This structure supports inserting and deleting lines by updating pointers. Once the required node is found, the pointer changes take constant time, O(1). Finding a line by its index takes O(L), where L is the number of lines.

## 3. Dynamic Character Array

Each document line contains a custom dynamic character array implemented in the `LineBuffer` class.

The class uses:

- `char* data` to store the characters.
- `int length` to track the number of characters.
- `int capacity` to track the allocated storage size.

When additional space is required, a new character array is allocated with increased capacity. The existing characters are copied into the new array, and the previous array is released.

The dynamic array supports inserting and deleting characters at specified positions. These operations may require shifting characters and therefore take O(n) time for a line containing n characters, excluding the cost of inserting additional characters.

## 4. File Handling

File operations are implemented using the `FileManager` class.

The class provides two main functions:

**Load:** Opens a text file using `ifstream`, reads its contents line by line, and stores them inside the document's doubly linked list.

**Save:** Uses `ofstream` to write document lines to a text file.

The implementation also handles invalid filenames and nonexistent files. A failed file-opening operation does not erase the document currently stored in memory.

## 5. Important Algorithms

### 5.1 Line Insertion Algorithm

The `insertLine()` function inserts a new line into the document using a doubly linked list.

**Algorithm:**

1. Check whether the requested line position is valid.
2. Create a new node containing the given text.
3. If inserting at the beginning, update the `head` pointer.
4. If inserting at the end, update the `tail` pointer.
5. If inserting in the middle, connect the new node to its previous and next nodes.
6. Increase the total line count.

**Time Complexity:** O(L + n), where L is the number of document lines and n is the length of the inserted text.

### 5.2 Character Insertion Algorithm

The `LineBuffer::insertText()` function inserts characters into the custom dynamic array.

**Algorithm:**

1. Validate the requested character position.
2. Check whether the array has enough capacity.
3. If necessary, create a larger array and copy the existing characters.
4. Shift the characters to the right to create space.
5. Insert the new characters.
6. Update the stored character count.

**Time Complexity:** O(n + m) amortized, where n is the original line length and m is the number of inserted characters.

### 5.3 Character Deletion Algorithm

The `LineBuffer::deleteText()` function deletes characters from a specified position.

**Algorithm:**

1. Check whether the starting position and deletion count are valid.
2. Shift the remaining characters to the left.
3. Reduce the stored character count.

**Time Complexity:** O(n), where n is the line length.

### 5.4 Line Deletion Algorithm

The `Document::deleteLine()` function removes a line from the doubly linked list.

**Algorithm:**

1. Find the node at the requested line index.
2. Check whether the node exists.
3. Update the neighboring nodes' `next` and `prev` pointers.
4. Update `head` or `tail` when necessary.
5. Delete the selected node and decrease the line count.

If only one line remains, the function clears its text rather than removing the final node.

**Time Complexity:** O(L + n), where n is the number of characters released from the deleted line.

### 5.5 Multiline Text Deletion

The `deleteTextRange()` function removes text between two positions, even when they belong to different lines.

**Algorithm:**

1. Validate the starting and ending positions.
2. Preserve the text before the starting position.
3. Preserve the text after the ending position.
4. Delete the selected characters.
5. Join the remaining text into the starting line.
6. Delete the unnecessary line nodes.

This algorithm combines dynamic-array operations with doubly linked-list operations.

### 5.6 Text Replacement Algorithm

The `replaceTextRange()` function replaces selected text with new text.

**Algorithm:**

1. Retrieve the original selected text using `getTextRange()`.
2. Delete the selected text using `deleteTextRange()`.
3. Insert the replacement characters.
4. If the replacement contains newline characters, split the line as required.
5. Return the original text so that the UndoManager can restore it later.

The same function can also perform insertion or deletion by using an empty selected range or an empty replacement string.

### 5.7 File Loading Algorithm

The `FileManager::load()` function opens a text file and loads its contents into the document.

**Algorithm:**

1. Validate the filename.
2. Open the file using `ifstream`.
3. Read the file line by line.
4. Insert each line into a temporary document.
5. Check for reading errors.
6. After successful reading, transfer the loaded text into the active document.

The temporary document helps prevent data loss when a file cannot be opened or read successfully.

### 5.8 File Saving Algorithm

The `FileManager::save()` function writes the current document to a text file.

**Algorithm:**

1. Validate the filename.
2. Open the output file using `ofstream`.
3. Traverse the document lines.
4. Write each line to the file.
5. Insert newline separators between lines.
6. Check whether writing and closing succeeded.

---

## 6. Time and Space Complexity Analysis

The following table summarizes the major operations implemented by Person A.

| Operation             | Time Complexity        | Explanation                                         |
| --------------------- | ---------------------- | --------------------------------------------------- |
| Get line count        | O(1)                   | Returns a stored variable                           |
| Find a line by index  | O(L)                   | Traverses the linked list                           |
| Insert a line         | O(L + n)               | Finds the position and copies the text              |
| Delete a line         | O(L + n)               | Finds and deletes the node and its characters       |
| Insert characters     | O(L + n + m) amortized | Finds a line and inserts m characters               |
| Delete characters     | O(L + n)               | Finds a line and shifts characters                  |
| Delete a word         | O(L + n)               | Finds word boundaries and removes characters        |
| Delete multiple lines | O(kL + D)              | Repeatedly deletes k lines, releasing D characters  |
| Split a line          | O(L + n)               | Separates text and inserts another line node        |
| Get character count   | O(L)                   | Visits each line                                    |
| Display document      | O(L + C)               | Traverses and displays all lines                    |
| Clear document        | O(L + C)               | Deletes the linked-list nodes and character buffers |
| Load file             | O(L² + C)              | Repeated indexed line operations                    |
| Save file             | O(L² + C)              | Repeated indexed line retrieval                     |

**Symbols used:**

- L = Number of lines in the document.
- n = Number of characters in the selected line.
- m = Number of characters being inserted.
- k = Number of lines being deleted.
- C = Total number of characters in the document.
- D = Total number of characters released from deleted lines.

The complexity of multiline replacement depends on the amount of text removed, the amount inserted, and the number of newline characters. Our implementation uses repeated string copying and linked-list traversals, so it is less efficient than an optimized editor.

### 6.1 Space Complexity

The doubly linked list requires memory for each node, including two pointers and its character buffer.

Each `LineBuffer` uses a dynamically allocated character array. Its capacity increases when more space is required.

The complete document therefore requires O(L + C) memory under the dynamic-array doubling strategy.

Some editing functions also use temporary strings to preserve or manipulate selected text, requiring additional memory proportional to the affected text.

### 6.2 Justification of Data Structures

**Doubly Linked List:** Suitable for representing document lines because nodes can be inserted or deleted by updating pointers without shifting every subsequent line.

**Dynamic Character Array:** Suitable for storing individual lines because characters can be accessed by index and memory capacity can grow when necessary.

**Custom Stack (Person B):** Suitable for Undo because the most recent editing operation must be reversed first, following Last In, First Out (LIFO).

Together, these structures provide a modular approach to document representation, editing, and undo functionality.
