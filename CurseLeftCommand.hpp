#ifndef CURSELEFT_HPP
#define CURSELEFT_HPP

#include "EditorModel.hpp"
#include "Command.hpp"
#include "EditorException.hpp"

class CurseLeft : public Command
{
public:
  virtual void execute(EditorModel& model)
  {
    model.rightCursor(false);
  }

  virtual void undo(EditorModel& model)
  {
    model.rightCursor(true);
  }
};

#endif //CURSELEFT_HPP
