#ifndef PRINTABLE_HPP
#define PRINTABLE_HPP

#include "EditorModel.hpp"
#include "Command.hpp"
#include <string>

class Printable : public Command
{
public:

  Printable(std::string str)
  {
    toAdd = str;
  }
  virtual void execute(EditorModel& model)
  {
    model.stringAdd(toAdd);
  }
  virtual void undo(EditorModel& model)
  {
    model.backspace();
  }
private:
  std::string toAdd;
};

#endif //PRINTABLE_HPP
