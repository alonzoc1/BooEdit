#ifndef NEWLINE_HPP
#define NEWLINE_HPP

#include "EditorModel.hpp"
#include "Command.hpp"

class NewLine:public Command
{
public:
  virtual void execute(EditorModel& model)
  {
    model.newLine();
  }
  virtual void undo(EditorModel& model)
  {
    model.backspace();
  }
};

#endif //NEWLINE_HPP
