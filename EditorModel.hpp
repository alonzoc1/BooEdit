// EditorModel.hpp
//
// ICS 45C Fall 2015
// Project #4: People Just Love to Play with Words
//
// The EditorModel class implements the "model" of BooEdit.  In other words, its
// job is to maintain the underlying data -- the current lines of text, where
// the cursor is supposed to be, etc. -- and provide operations that allow the
// EditorView to access that data, along with basic operations that allow the
// various Command objects to make the necessary changes when they're executed
// or undone.
//
// The member functions already declared in the EditorModel class are absolutely
// necessary for EditorView to work, so they cannot be removed or have their
// declarations changed (though you may need to implement them; see
// EditorModel.cpp).
//
// You will absolutely need to implement additional member functions, because I
// haven't declared any functions that change the editor's data (e.g., by
// inserting characters, moving the cursor), which you'll need in order to
// implement the various Command objects.  You may also need additional member
// functions that access the editor's data in ways not provided here.
//
// When adding member functions, focus on adding "primitive" tools that you
// might be able to use in multiple command implementations.  Don't just add
// one member function for each command; that's tying your design to the
// specifics of the commands you chose, which makes it more difficult to
// change your mind about which commands you want without having a cascading
// effect here.
//
// The EditorModel class is unaware of the concept of "undo"; it is the job of
// the Command objects to know what they need to do in order to undo a Command.
// This may mean that your Command objects will need to store information in
// member variables after execute() is finished, so that information will still
// be available at the time undo() is called.
//
// Note that the notion of "line number" and "column number" here is one-based,
// not zero-based, which means that the top left corner of the file is line 1
// column 1.  You can handle this however you'd like inside of your class, but
// the rest of BooEdit expects Editor objects to take and return one-based
// line and column numbers.

#ifndef EDITORMODEL_HPP
#define EDITORMODEL_HPP

#include <string>
#include "EditorException.hpp"
#include <vector>
#include "DeleteLineData.hpp"



class EditorModel
{
public:
    // Initializes the editor model.  Initially, the cursor is on
    // line 1 column 1 and there should be one empty line of text
    // in the editor.
    EditorModel();

    // Returns the line number where the cursor currently should reside.
    int cursorLine() const;

    // Returns the column number where the cursor currently should reside.
    int cursorColumn() const;

    // Returns the number of lines of text currently in the editor.
    int lineCount() const;

    // Returns the text on the given line number.
    const std::string& line(int lineNumber) const;

    // Returns the error message that should be displayed currently.
    const std::string& currentErrorMessage() const;

    // Sets the error message that should be displayed currently.
    void setErrorMessage(const std::string& errorMessage);

    // Clears the error message that should be displayed currently.
    void clearErrorMessage();

  // Moves cursor right if passed true, left if passed false
  void rightCursor(bool direction);

  // Returns string length of current line
  int charCount() const;

  // Adds a string to at the current cursor position and moves cursor to end
  void stringAdd(std::string typed);

  // Deletes the character before the cursor's current position and returns it
  std::string backspace();

  void newLine();

  // Moves cursor up if passed true, else down
  // also returns previous cursor position for undoing purposes
  int upCursor(bool direction);

  //Use with caution, sets exact cursor Column and relative Line
  void moveCursor(int col, int lin);

  //Moves cursor home and returns old column
  int curseHome();

  //Moves cursor to end and returns old column
  int curseEnd();

  //Deletes line cursor is at, returns a class called DelLineData which
  //stores both a) the column the cursor was at before the delete and
  //b) the string associated with the line itself, for undoing purposes
  DelLineData deleteLine();

  //Even more powerful than moveCursor, this function places the cursor
  //on the exact coordinates given (as opposed to relative coords)
  void exactCursorPos(int col, int lin);

  //Adds a line back to where it was before, according to the passed
  //DelLineData object. Does NOT reposition the cursor, that is done
  //In the command object using exactCursorPos.
  void undeleteLine(DelLineData data);
  
private:
    // Write declarations for any private member variables here.
    // Additionally, you can add any private member functions you'd like.
  int currentColumn = 1;
  int currentLine = 1;
  std::string curErrorMessage = "";
  std::vector<std::string> text;
  
};



#endif // EDITORMODEL_HPP

