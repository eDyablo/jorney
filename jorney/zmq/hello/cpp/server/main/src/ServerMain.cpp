#include <string>
#include <iostream>
#include "zmq.hpp"
#include "basics/Thread.h"

namespace zmqhello {
	class Server {
	public:
		Server(std::string const& anEndpoint) :
			endpoint(anEndpoint),
			context(1),
			channel(context, ZMQ_REP) {
		}

		void run() {
			initialize();
			communicate();
		}

	private:
		void initialize() {
			std::cout << "Ready to service requests from " << endpoint << " ...\n";
			if (useBroker())
				channel.connect("tcp://" + endpoint);
			else
				channel.bind("tcp://" + endpoint);
		}

		bool useBroker() const {
			return endpoint.find_first_of('*') != 0;
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
			basics::sleep(1);
		}

	private:
		std::string endpoint;
		zmq::context_t context;
		zmq::socket_t channel;
	};
}

int main(int argc, char* argv[]) {
	std::string endpoint = "localhost:5560";
	if (argc > 1)
		endpoint = argv[1];
	zmqhello::Server server(endpoint);
	server.run();
	return 0;
}