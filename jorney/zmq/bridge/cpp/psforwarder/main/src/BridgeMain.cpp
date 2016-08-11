#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "Programm.hpp"

int main(int argc, char* argv[]) {
	try {
		std::vector<std::string> parameters;
		std::copy(&argv[1], &argv[argc], std::back_inserter(parameters));
		zmqbridge::Programm programm;
		programm.run(parameters);
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