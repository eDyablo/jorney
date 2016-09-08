#include "VentilatorProgramm.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
  try {
    std::vector<std::string> args;
    std::copy(&argv[1], &argv[argc], std::back_inserter(args));
    zmqparallel::VentilatorProgramm programm;
    programm.run(args);
    return 0;
  }
  catch (std::exception const& e) {
    std::cerr << e.what() << ".\n";
  }
  catch (...) {
    std::cerr << "Something went wrong.\n";
  }
}