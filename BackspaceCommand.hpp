#ifndef BACKSPACE_HPP
#define BACKSPACE_HPP

#include "EditorModel.hpp"
#include "Command.hpp"
#include <string>

class Backspace:public Command
{
public:
  virtual void execute(EditorModel& model)
  {
    character = model.backspace();
  }
  virtual void undo(EditorModel& model)
  {
    if (character.length() == 1)
      model.stringAdd(character);
    else
      {
        model.newLine();
      }
  }

private:
  std::string character;
};

#endif //BACKSPACE_HPP
