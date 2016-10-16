#ifndef DELETELINE_HPP
#define DELETELINE_HPP

#include "EditorModel.hpp"
#include "Command.hpp"
#include "EditorException.hpp"

#include "DeleteLineData.hpp"

class DeleteLine : public Command
{
public:
  virtual void execute(EditorModel& model)
  {
    stored = model.deleteLine();
  }

  virtual void undo(EditorModel& model)
  {
    model.undeleteLine(stored);
    model.exactCursorPos(stored.oldColumn, stored.oldLine);
  }
private:
  DelLineData stored;
};

#endif //DELETELINE_HPP
