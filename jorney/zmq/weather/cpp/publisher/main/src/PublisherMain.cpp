
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "PublisherProgramm.hpp"

int main(int argc, char* argv[]) {
	try {
		std::vector<std::string> args;
		std::copy(&argv[1], &argv[argc], std::back_inserter(args));
		zmqweather::PublisherProgramm program;
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