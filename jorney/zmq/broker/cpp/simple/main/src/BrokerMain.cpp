#include "Broker.hpp"
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>

int main(int argc, char* argv[]) {
	unsigned int frontend = 5559, backend = 5560;
	if (argc > 2) {
		std::stringstream params;
		std::copy(&argv[1], &argv[argc], std::ostream_iterator<char*>(params, " "));
		params >> frontend >> backend;
	}	
	zmqbroker::SimpleBroker broker(frontend, backend);
	broker.run();
	return 0;
}