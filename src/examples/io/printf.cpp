#include "sophia/io/printf.hpp"

#include <iostream>

struct unprintable { };

int main()
  {
  sophia::io::printf("{1} is second argument, {0} is the first!\n", 1337, 42);
  sophia::io::printf("{0}\n", unprintable{});
  }
