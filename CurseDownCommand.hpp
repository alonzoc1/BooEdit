#ifndef CURSEDOWN_HPP
#define CURSEDOWN_HPP

#include "EditorModel.hpp"
#include "Command.hpp"
#include "EditorException.hpp"

class CurseDown : public Command
{
public:
  virtual void execute(EditorModel& model)
  {
    oldColumn = model.upCursor(false);
  }

  virtual void undo(EditorModel& model)
  {
    model.moveCursor(oldColumn, -1);
  }
private:
  int oldColumn = 0;
};

#endif //CURSEUP_HPP
