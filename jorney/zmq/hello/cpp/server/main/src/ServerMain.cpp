#include <string>
#include <iostream>

#include "zmq.hpp"
#include "basics/Thread.h"

int main() {
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_REP);
	socket.bind("tcp://*:5555");
	while (true) {
		zmq::message_t request;
		socket.recv(&request);
		std::cout << "Received Hello" << std::endl;
		basics::sleep(1);
		zmq::message_t reply (5);
		::memcpy(reply.data (), "World", 5);
		socket.send(reply);
		basics::sleep(1);
	}
	return 0;
}