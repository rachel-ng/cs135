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
      if(line[i]==c)
	{
	  result++;
	}
    }
  return result;
}

std::string indentspacer(std::string input)
{
  static int tracker = 0;
  int numstart = countChar(input, '{');
  int numend = countChar(input, '}');
  std::string result = input;
  for(int i =0; i < tracker; i++)
    {
      result = '\t' + result;
    }
  tracker += numstart;
  tracker -= numend;
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
    output = indentspacer(output);
    return output;
  fin.close();
}

std::string indent()
{
  int tracker = 0;
  std::string result="";
  std::string input = unindent();
  result = indentspacer(input);
  return result;
}
