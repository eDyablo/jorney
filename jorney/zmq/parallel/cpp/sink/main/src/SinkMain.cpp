#include "zmq.hpp"
#include <chrono>
#include <iostream>

int main() {
	zmq::context_t context(1);
	zmq::socket_t receiver(context,ZMQ_PULL);
	receiver.bind("tcp://*:5558");

	zmq::message_t message;
	receiver.recv(&message);

	auto start = std::chrono::steady_clock::now();

	int const taskNumber = 100;
	int total_msec = 0;
	for (int taskIndex = 0; taskIndex < taskNumber; taskIndex++) {
		receiver.recv(&message);
		if ((taskIndex / 10) * 10 == taskIndex)
			std::cout << ":";
		else
			std::cout << ".";
	}

	auto end = std::chrono::steady_clock::now();
	auto interval = std::chrono::duration_cast<std::chrono::milliseconds>(
			end - start).count();

	std::cout << "\nCost:" << interval << " msec\n";
	return 0;
}