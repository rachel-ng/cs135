#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "funcs.h"
int main()
{
  std::string test1 = "       test1";
  std::cout << "This should print one with spaces" << '\n' << test1 << std::endl;
  std::cout << "This should print one without spaces" << '\n' << removeLeadingSpaces(test1) << std::endl;
  std::cout << "This should print code without any indents" << std::endl;
  std::string result = unindent();
}
