#include "ServerProgramm.hpp"

#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
	try {
		std::vector<std::string> args;
		std::copy(&argv[1], &argv[argc], std::back_inserter(args));
		zmqhello::ServerProgramm program;
		program.run(args);
		return 0;
	}
	catch (std::exception const& e) {
		std::cout << e.what() << "\n";
		return 1;
	}
	catch (...) {
		std::cout << "Something went wrong\n";
		return 2;
	}
}