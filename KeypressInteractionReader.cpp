// KeypressInteractionReader.cpp
//
// ICS 45C Fall 2015
// Project #4: People Just Want to Play with Words
//
// Implementation of the KeypressInteractionReader
//
// YOU WILL NEED TO IMPLEMENT SOME THINGS HERE

#include "KeypressInteractionReader.hpp"

//Including command headers
#include "CurseRightCommand.hpp"
#include "CurseLeftCommand.hpp"
#include "PrintableCommand.hpp"
#include "BackspaceCommand.hpp"
#include "NewLineCommand.hpp"
#include "CurseDownCommand.hpp"
#include "CurseUpCommand.hpp"
#include "HomeCommand.hpp"
#include "EndCommand.hpp"
#include "DeleteLineCommand.hpp"

#include <string>
// You will need to update this member function to watch for the right
// keypresses and build the right kinds of Interactions as a result.
//
// The reason you'll need to implement things here is that you'll need
// to create Command objects, which you'll be declaring and defining
// yourself; they haven't been provided already.
//
// I've added handling for "quit" here, but you'll need to add the others.



Interaction KeypressInteractionReader::nextInteraction()
{

    while (true)
    {
        Keypress keypress = keypressReader.nextKeypress();
        

        if (keypress.ctrl())
        {
            // The user pressed a Ctrl key (e.g., Ctrl+X); react accordingly

            switch (keypress.code())
            {
            case 'X':
              {
                return Interaction::quit();
                break;
              }
            case 'Z':
              {
                return Interaction::undo();
              }
            case 'A':
              {
                return Interaction::redo();
              }
            case 'O':
              {
                CurseRight* CrsRight = new CurseRight;
                return Interaction::command(CrsRight);
              }
            case 'U':
              {
                CurseLeft* CrsLeft = new CurseLeft;
                return Interaction::command(CrsLeft);
              }
            case 'H':
              {
                Backspace* BckSpc = new Backspace;
                return Interaction::command(BckSpc);
              }
            case 'J':
              {
                NewLine* NwLn = new NewLine;
                return Interaction::command(NwLn);
              }
            case 'M':
              {
                NewLine* NwLn = new NewLine;
                return Interaction::command(NwLn);
              }
            case 'I':
              {
                CurseUp* CrsUp = new CurseUp;
                return Interaction::command(CrsUp);
              }
            case 'K':
              {
                CurseDown* CrsDn = new CurseDown;
                return Interaction::command(CrsDn);
              }
            case 'Y':
              {
                Home* Hm = new Home;
                return Interaction::command(Hm);
              }
            case 'P':
              {
                End* Ed = new End;
                return Interaction::command(Ed);
              }
            case 'D':
              {
                DeleteLine* DL = new DeleteLine;
                return Interaction::command(DL);
              }
            }
        }
        else
        {
          std::string strungChar = "";
          strungChar += keypress.code();
          Printable* PrntChar = new Printable(strungChar);
          return Interaction::command(PrntChar);
        }
    }
}

