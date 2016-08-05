#include "Broker.hpp"
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>

int main(int argc, char* argv[]) {
	if (argc < 3) {
		std::cout << "Specify frontend and backend ports\n";
		return 1;
	}
	std::stringstream params;
	std::copy(&argv[1], &argv[argc], std::ostream_iterator<char*>(params, " "));
	unsigned int frontend, backend;
	params >> frontend >> backend;
	zmqbroker::SimpleBroker broker(frontend, backend);
	broker.run();
	return 0;
}