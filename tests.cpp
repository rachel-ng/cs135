#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "funcs.h"
TEST_CASE("Checks if spaces before first character is removed")
{
  CHECK(removeLeadingSpaces("  first test")=="first test");
}
