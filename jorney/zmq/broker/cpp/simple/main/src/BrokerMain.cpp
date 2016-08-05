#include "Broker.hpp"

int main() {
	zmqbroker::SimpleBroker broker(5559, 5560);
	broker.run();
	return 0;
}