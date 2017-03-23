#include "sophia/flow/guard.hpp"
#include "sophia/io/printf.hpp"

void handle_answer(int answer)
  {
  using namespace sophia;

  flow::guard(answer == 42, "The answer is wrong!!") or [](auto const & message){
    io::printf("I guess we will die because: '{0}'. Goodbye cruel world...\n\n", message);
  };

  io::printf("I am sure this is the right answer: {0}\n", answer);
  }

int main() try
  {
  handle_answer(41);
  }
catch (...)
  {
  // We cannot catch the guard_violation
  }
