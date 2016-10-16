#ifndef CURSERIGHT_HPP
#define CURSERIGHT_HPP

#include "EditorModel.hpp"
#include "Command.hpp"
#include "EditorException.hpp"

class CurseRight : public Command
{
public:
  virtual void execute(EditorModel& model)
  {
    model.rightCursor(true);
  }

  virtual void undo(EditorModel& model)
  {
    model.rightCursor(false);
  }
};

#endif //CURSERIGHT_HPP
