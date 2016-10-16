#ifndef HOME_HPP
#define HOME_HPP

#include "EditorModel.hpp"
#include "Command.hpp"
#include "EditorException.hpp"

class Home : public Command
{
public:
  virtual void execute(EditorModel& model)
  {
    oldColumn = model.curseHome();
  }

  virtual void undo(EditorModel& model)
  {
    model.moveCursor(oldColumn, 0);
  }
private:
  int oldColumn = 0;
};

#endif //HOME_HPP
