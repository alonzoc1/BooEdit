// EditorModel.cpp
//
// ICS 45C Fall 2015
// Project #4: People Just Love to Play with Words
//
// Implementation of the EditorModel class

#include "EditorModel.hpp"
#include "EditorException.hpp"

#include <string>
#include <vector>
#include "DeleteLineData.hpp"

EditorModel::EditorModel()
{
  std::string startString = "";
  text.push_back(startString);
}


int EditorModel::cursorLine() const
{
    return currentLine;
}


int EditorModel::cursorColumn() const
{
    return currentColumn;
}


int EditorModel::lineCount() const
{
  return text.size();
}


const std::string& EditorModel::line(int lineNumber) const
{
  int tempNumber;
  tempNumber = lineNumber;
  tempNumber--;
  return text[tempNumber];
}


const std::string& EditorModel::currentErrorMessage() const
{
    return curErrorMessage;
}


void EditorModel::setErrorMessage(const std::string& errorMessage)
{
  curErrorMessage = errorMessage;
}


void EditorModel::clearErrorMessage()
{
  curErrorMessage = "";
}

void EditorModel::rightCursor(bool direction)
{
  if (direction == true)
    {
      int maxLine = lineCount();
      int curLine = cursorLine();
      int maxLength = charCount() + 1;
      int curLength = cursorColumn();
      if (curLine == maxLine)
        {
          if (maxLength == curLength)
            {
              EditorException error("Already at end");
              throw error;
            }
        }
      if (maxLength > curLength)
        {
          currentColumn++;
        }
      if (maxLength == curLength)
        {
          currentLine++;
          currentColumn = 1;
        }
    }
  else if (direction == false)
    {
      int curLine = cursorLine();
      int curLength = cursorColumn();
      if (curLine == 1)
        {
          if (curLength == 1)
            {
              EditorException error("Already at beginning");
              throw error;
            }
        }
      if (curLength > 1)
        {
          currentColumn--;
        }
      if (curLength == 1)
        {
          currentLine--;
          currentColumn = charCount() + 1;
        }
    }
}

int EditorModel::charCount() const
{
  std::string raw01 = line(currentLine);
  int length = raw01.length();
  return length;
}

void EditorModel::stringAdd(std::string typed)
{
  int lineNumber = cursorLine();
  int columnNumber = cursorColumn();
  lineNumber--;
  {
    columnNumber--;
    std::string newline = text[lineNumber];
    newline.insert(columnNumber,typed);
    text.insert(text.begin()+lineNumber, newline);
    text.erase(text.begin()+lineNumber+1);
    rightCursor(true);
  }
}

std::string EditorModel::backspace()
{
  int lineToDelete = cursorLine();
  int columnToDelete = cursorColumn();
  //the deleted character to be returned, if there is one
  std::string popped = ""; 
  columnToDelete--;
  if ((lineToDelete-1) == 0)
    {
      if (columnToDelete == 0)
        {
          EditorException error ("Already at beginning");
          throw error;
        }
    }
  if (columnToDelete != 0)
    {
      std::string subS01;
      std::string subS02;
      lineToDelete--;
      std::string rawS = text[lineToDelete];
      lineToDelete++;
      popped = rawS[columnToDelete-1];//the deleted character
      int j = rawS.length();
      j = j - (columnToDelete);
      if (columnToDelete-1 == 0)
        {
          subS01 = "";
        }
      else
        {
          subS01 = rawS.substr(0,columnToDelete-1);
        }
      subS02 = rawS.substr(columnToDelete,j);
      subS01 += subS02;
      lineToDelete--;
      text.insert(text.begin()+lineToDelete, subS01);
      text.erase(text.begin()+lineToDelete+1);
      rightCursor(false);
    }
  else
    {
      currentLine--;
      int endPos = charCount();
      currentLine++;
      lineToDelete--;
      std::string rawS = text[lineToDelete];
      lineToDelete--;
      std::string prevRawS = text[lineToDelete];
      prevRawS += rawS;
      text.insert(text.begin()+lineToDelete, prevRawS);
      text.erase(text.begin()+lineToDelete+2);
      text.erase(text.begin()+lineToDelete+1);
      currentLine--;
      currentColumn = endPos+1;
    }
  return popped;
}

void EditorModel::newLine()
{
  int columnPos = currentColumn;
  int linePos = currentLine;
  int maxColumn = charCount();
  std::string lineToAdd;
  std::string raw = text[linePos-1];
  std::string lineToUpdate = text[linePos-1];  
  if (maxColumn != columnPos)
    {
      int b = maxColumn;
      b = b - columnPos;
      lineToAdd = raw.substr(columnPos-1,b+1);
      lineToUpdate = raw.substr(0,columnPos-1);
      
    }
  text.insert(text.begin()+linePos-1, lineToUpdate);
  text.erase(text.begin()+linePos);
  text.insert(text.begin()+linePos, lineToAdd);
  currentColumn = 1;
  currentLine++;
}

int EditorModel::upCursor(bool direction)
{
  int oldCol = currentColumn;
  if (direction == true)
    {
      if (currentLine <= 1)
        {
          EditorException error("Already at top");
          throw error;
        }
      currentLine--;
      int maxAboveLine = charCount();
      currentLine++;
      if (maxAboveLine >= currentColumn-1)
        {
          currentLine--;
        }
      if (maxAboveLine < currentColumn-1)
        {
          currentLine--;
          currentColumn = maxAboveLine+1;
        }
    }
  else
    {
      if (currentLine >= text.size())
        {
          EditorException error("Already at bottom");
          throw error;
        }
      currentLine++;
      int maxBelowLine = charCount();
      currentLine--;
      if (maxBelowLine >= currentColumn-1)
        {
          currentLine++;
        }
      if (maxBelowLine < currentColumn-1)
        {
          currentLine++;
          currentColumn = maxBelowLine+1;
        }
    }
  return oldCol;
}

void EditorModel::moveCursor(int col, int lin)
{
  currentColumn = col;
  currentLine += lin;
}

int EditorModel::curseHome()
{
  int oldCol = currentColumn;
  currentColumn = 1;
  return oldCol;
}

int EditorModel::curseEnd()
{
  int oldCol = currentColumn;
  currentColumn = 1 + charCount();
  return oldCol;
}

DelLineData EditorModel::deleteLine()
{
  int oldColumn = currentColumn;
  int oldLine = currentLine;
  bool delOnly = false;
  bool delLast = false;
  std::string targetLine = text[currentLine-1];
  if (text.size() == 1)
    {
      std::string empty = "";
      if (text[0] == empty)
        {
          EditorException error("Already empty");
          throw error;
        }
      delOnly = true;
      currentColumn = 1;
      currentLine = 1;
      text[0] = empty;
    }
  else if (currentLine != text.size()) //if its not the last line
    {
      text.erase(text.begin()+currentLine-1);
      if (currentColumn > (charCount()+1))
        {
          currentColumn = charCount() + 1;
        }
    }
  else //if it is the last line
    {
      delLast = true;
      text.erase(text.begin()+currentLine-1);
      currentLine--;
      if (currentColumn > (charCount()+1))
        {
          currentColumn = charCount() + 1;
        }
    }
  DelLineData store(oldColumn,oldLine,targetLine, delOnly, delLast);
  return store;
}

void EditorModel::exactCursorPos(int col, int lin)
{
  currentLine = lin;
  currentColumn = col;
}

void EditorModel::undeleteLine(DelLineData data)
{
  if (data.delOnly == true)
    {
      text[0] = data.deletedLine;
    }
  else if (data.delLast == true)
    {
      text.push_back(data.deletedLine);
    }
  else
    {
      text.insert(text.begin() + data.oldLine - 1,data.deletedLine);
    }
}
