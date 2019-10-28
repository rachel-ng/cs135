#include <iostream>
#include <fstream>
std::string removeLeadingSpaces(std::string line)
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
int countChar(std::string line, char c)
{
  int result;
  for(int i =0; i < line.length();i++)
    {
      if(line[i]=c)
	{
	  result++;
	}
    }
  return result;
}
std::string unindent()
{
  std::string output;
  std::string line;
  std::ifstream fin("bad-code.cpp");
  while(getline(fin, line))
    {
      output = removeLeadingSpaces(line);
      std::cout << output << std::endl;
    }
}
std::string indent(std::string input)
{
}
