#include "sophia/io/io.hpp"

int main()
  {
  auto number = 42;
  auto string = "The answer";
  sophia::io::writeln(string, " is ", number);
  }
