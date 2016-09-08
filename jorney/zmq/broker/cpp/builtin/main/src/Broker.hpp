#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "zmq.hpp"

namespace zmqbroker {
	class BuiltinBroker {
	public:
		BuiltinBroker(unsigned int aFrontendPort, unsigned int aBackendPort) :
			frontendPort(aFrontendPort),
			backendPort(aBackendPort),
			context(1),
			frontend(context, ZMQ_ROUTER),
			backend(context, ZMQ_DEALER) {
			items[0] = pollin(frontend);
			items[1] = pollin(backend);
		}

		void run() {
			initialize();
			communicate();
		}

	private:
		static zmq::pollitem_t pollin(zmq::socket_t& socket) {
			zmq::pollitem_t item = { socket, 0, ZMQ_POLLIN, 0 };
			return item;
		}

		void initialize() {
			frontend.bind(endpoint(frontendPort));
			backend.bind(endpoint(backendPort));
			std::cout << "Broker's frontend is " << frontendPort
					<< " and backend is " << backendPort << "\n";
		}

		std::string endpoint(int port) const {
			std::stringstream text;
			text << "tcp://*:" << port;
			return text.str();
		}

		void communicate() {
			zmq::proxy(frontend, backend, 0);
		}

	private:
		unsigned int frontendPort;
		unsigned int backendPort;
		zmq::context_t context;
		zmq::socket_t frontend;
		zmq::socket_t backend;
		zmq::pollitem_t items[2];
	};
}