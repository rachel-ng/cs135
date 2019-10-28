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
  int result=0;
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
std::string indentspacer(std::string input)
{
  std::string result = result;
  static int tracker = 0;
  int numstarts=0; int numends=0;

  for(int i =0; i < tracker; i++)
    {
      result = '\t' + input;
    }
  numstarts = countChar(result, '{');
  tracker += numstarts;
  numends = countChar(result,'}');
  tracker -= numends;
  return result;
}
std::string indent()
{
  std::string result;
  std::string line;
  std::ifstream fin("bad-code.cpp");
  while(getline(fin, line))
    {
      result += indentspacer(line);
      result += '\n';
    }
  std::cout << result << std::endl;
}
