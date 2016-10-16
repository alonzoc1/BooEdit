#ifndef DELETELINEDATA_HPP
#define DELETELINEDATA_HPP

#include <string>
class DelLineData
{
public:
  DelLineData()
  {
    oldColumn = 0;
  }
  DelLineData(int oldCol, int oldLin, std::string delLine,
              bool dOnly, bool dLast)
  {
    oldColumn = oldCol;
    deletedLine = delLine;
    oldLine = oldLin;
    delOnly = dOnly;
    delLast = dLast;
  }
  int oldColumn;
  std::string deletedLine;
  int oldLine;
  bool delOnly;
  bool delLast;
};

#endif //DELETELINEDATA_HPP
