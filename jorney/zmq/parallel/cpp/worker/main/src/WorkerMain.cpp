#include <string>
#include <iostream>
#include <sstream>
#include "zmq.hpp"
#include "basics/Thread.h"

int main() {
	zmq::context_t context(1);
	zmq::socket_t ventilator(context, ZMQ_PULL);
	ventilator.connect("tcp://localhost:5557");
	zmq::socket_t sink(context, ZMQ_PUSH);
	sink.connect("tcp://localhost:5558");
	while (true) {
		zmq::message_t message;
		int workload;
		ventilator.recv(&message);
		std::string smessage(static_cast<char*>(message.data()), message.size());
		std::istringstream iss(smessage);
		iss >> workload;
		basics::msleep(workload);
		message.rebuild();
		sink.send(message);
		std::cout << workload << " ";
	}
	return 0;
}