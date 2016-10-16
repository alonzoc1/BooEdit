#ifndef END_HPP
#define END_HPP

#include "EditorModel.hpp"
#include "Command.hpp"
#include "EditorException.hpp"

class End : public Command
{
public:
  virtual void execute(EditorModel& model)
  {
    oldColumn = model.curseEnd();
  }

  virtual void undo(EditorModel& model)
  {
    model.moveCursor(oldColumn, 0);
  }
private:
  int oldColumn = 0;
};

#endif //END_HPP
