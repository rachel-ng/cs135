#include <iostream>
string removeLeadingSpaceS(std::string line)
{
  std::string output;
  bool isspacebeforeword = true;
  int tracker = 0;
  while(isspacebeforeword)
    {
      if(isspace(line[tracker])!=0)
	{
	  tracker++;
	}
      else
	{
	  isspacebeforeword = false;
	}
    }
  output = line.substr(tracker, line.length()-1);
  return output;
}
