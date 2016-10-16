#ifndef CURSEUP_HPP
#define CURSEUP_HPP

#include "EditorModel.hpp"
#include "Command.hpp"
#include "EditorException.hpp"

class CurseUp : public Command
{
public:
  virtual void execute(EditorModel& model)
  {
    oldColumn = model.upCursor(true);
  }

  virtual void undo(EditorModel& model)
  {
    model.moveCursor(oldColumn,1);
  }
private:
  int oldColumn = 0;
};

#endif //CURSEUP_HPP
