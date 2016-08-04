#include <string>
#include <iostream>
#include "zmq.hpp"
#include "basics/Thread.h"

namespace zmqhello {
	class Server {
	public:
		Server() :
			context(1),
			channel(context, ZMQ_REP) {
		}

		void run() {
			initialize();
			communicate();
		}

	private:
		void initialize() {
			channel.bind("tcp://*:5555");
		}

		void communicate() {
			while (true)
				processRequest();
		}

		void processRequest() {
			std::cout << "Received " << receive() << std::endl;
			busy();
			replay("World");
		}

		std::string receive() {
			zmq::message_t request;
			channel.recv(&request);
			return std::string((char*)request.data(), request.size());
		}

		void replay(std::string const& text) {
			zmq::message_t reply(text.size());
			::memcpy(reply.data(), text.c_str(), text.size());
			channel.send(reply);
		}

		void busy() {
			basics::msleep(500);
		}

	private:
		zmq::context_t context;
		zmq::socket_t channel;
	};
}

int main() {
	zmqhello::Server server;
	server.run();
	return 0;
}