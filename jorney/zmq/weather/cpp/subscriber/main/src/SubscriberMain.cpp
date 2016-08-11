#include <algorithm>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "zmq.hpp"
#include "SubscriberProgramm.hpp"

int main(int argc, char* argv[]) {
  try {
    std::vector<std::string> args;
    std::copy(&argv[1], &argv[argc], std::back_inserter(args));
    zmqweather::SubscriberProgramm program;
    program.run(args);
    return 0;
  }
  catch (std::exception const& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (...) {
    std::cerr << "Something went wrong\n";
  }
}