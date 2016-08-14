#include <iostream>
#include "zmq.hpp"

int main() {
	zmq::context_t context(1);
	zmq::socket_t receiver(context,ZMQ_PULL);
	receiver.bind("tcp://*:5558");

	zmq::message_t message;
	receiver.recv(&message);

	int const taskNumber = 100;
	int total_msec = 0;
	for (int taskIndex = 0; taskIndex < taskNumber; taskIndex++) {
		receiver.recv(&message);
		if ((taskIndex / 10) * 10 == taskIndex)
			std::cout << ":" << std::flush;
		else
			std::cout << "." << std::flush;
	}
	std::cout << "\n";
	return 0;
}