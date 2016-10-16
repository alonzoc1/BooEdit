// InteractionProcessor.cpp
//
// ICS 45C Fall 2015
// Project #4: People Just Love to Play with Words
//
// Implementation of the InteractionProcessor class

#include "InteractionProcessor.hpp"
#include "EditorException.hpp"
#include "Interaction.hpp"

#include <vector>

// This function implements command execution, but does not handle "undo"
// and "redo"; you'll need to add that handling.

std::vector<Command*> undoStack;
std::vector<Command*> redoStack;

void InteractionProcessor::run()
{
  undoStack.reserve(5);
  redoStack.reserve(5);
    view.refresh();

    while (true)
    {
        Interaction interaction = interactionReader.nextInteraction();

        if (interaction.type() == InteractionType::quit)
        {
          int undoSize = undoStack.size();
          for (int i = 0; i < undoSize; i++)
            {
              delete undoStack[i];
            }
          int redoSize = redoStack.size();
          for (int j = 0; j < redoSize; j++)
            {
              delete redoStack[j];
            }
            break;
        }
        else if (interaction.type() == InteractionType::undo)
        {
          Command* undoTarget;
          int latestIndex = undoStack.size();
          bool doNothing = false;
          if (latestIndex == 0)
            {
              doNothing = true;
            }
          if (doNothing == false)
            {
              latestIndex--;
              undoTarget = undoStack[latestIndex];
              try
                {
                  undoTarget->undo(model);
                  model.clearErrorMessage();
                  undoStack.pop_back();
                  redoStack.push_back(undoTarget);
                }
              catch (EditorException& e)
                {
                  model.setErrorMessage(e.getReason());
                }
            }
          view.refresh();
        }
        else if (interaction.type() == InteractionType::redo)
        {
          Command* redoTarget;
          int latestIndex = redoStack.size();
          bool doNothing = false;
          if (latestIndex == 0)
            {
              doNothing = true;
            }
          if (doNothing == false)
            {
              latestIndex--;
              redoTarget = redoStack[latestIndex];
              try
                {
                  redoTarget->execute(model);
                  model.clearErrorMessage();
                  redoStack.pop_back();
                  undoStack.push_back(redoTarget);
                }
              catch (EditorException& e)
                {
                  model.setErrorMessage(e.getReason());
                }
            }
          view.refresh();
        }
        else if (interaction.type() == InteractionType::command)
        {
            Command* command = interaction.command();

            try
            {
                command->execute(model);
                model.clearErrorMessage();
                undoStack.push_back(command);
                redoStack.clear();
            }
            catch (EditorException& e)
            {
                model.setErrorMessage(e.getReason());
            }

            view.refresh();

            // Note that you'll want to be more careful about when you delete
            // commands once you implement undo and redo.  For now, since
            // neither is implemented, I've just deleted it immediately
            // after executing it.  You'll need to wait to delete it until
            // you don't need it anymore.
        }
    }
}

