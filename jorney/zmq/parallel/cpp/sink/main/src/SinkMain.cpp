#include "SinkProgramm.hpp"
#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
  try {
    std::vector<std::string> args;
    std::copy(&argv[1], &argv[argc], back_inserter(args));
    zmqparallel::SinkProgramm programm;
    programm.run(args);
    return 0;
  }
  catch (std::exception const& e) {
    std::cerr << e.what() << ".\n";
    return 1;
  }
  catch (...) {
    std::cerr << "Something went wrong.\n";
    return 2;
  }
}