#pragma once

#include "zmq.hpp"

#include <iostream>
#include <thread>
#include <chrono>

namespace zmqhello {
	void worker(zmq::context_t* context) {
		zmq::socket_t socket(*context, ZMQ_REP);
		socket.connect("inproc://workers");
		while (true) {
			zmq::message_t request;
			socket.recv(&request);
			std::cout << std::this_thread::get_id() << " Received request: [" << (char*)request.data() << "]\n";

			std::this_thread::sleep_for(std::chrono::seconds(1));

			zmq::message_t reply (6);
			::memcpy((void*)reply.data(), "World", 6);
			socket.send(reply);
		}
	}
}