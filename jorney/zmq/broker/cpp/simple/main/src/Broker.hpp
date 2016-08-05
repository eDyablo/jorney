#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "zmq.hpp"

namespace zmqbroker {
	class SimpleBroker {
	public:
		SimpleBroker(unsigned int aFrontendPort, unsigned int aBackendPort) :
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
			while (true) {
				poll();
				process();
			}
		}

		void poll() {
			zmq::poll(&items[0], 2, -1);
		}

		void process() {
			processClient();
			processService();
		}

		void processClient() {
			if (hasMessage(items[0]))
				translateMessage(frontend, backend);
		}

		void processService() {
			if (hasMessage(items[1]))
				translateMessage(backend, frontend);
		}

		bool hasMessage(zmq::pollitem_t const& item) const {
			return item.revents & ZMQ_POLLIN;
		}

		void translateMessage(zmq::socket_t& from, zmq::socket_t& to) {
			zmq::message_t message;
			do {
				from.recv(&message);
				to.send(message, message.more() ? ZMQ_SNDMORE : 0);
			} while (message.more());
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