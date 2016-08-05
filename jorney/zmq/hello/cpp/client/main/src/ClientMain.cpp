#include <string>
#include <iostream>
#include "zmq.hpp"

namespace zmqhello {
	class Client {
	public:
		Client(std::string const& anEndpoint) :
			endpoint(anEndpoint),
			context(1),
			channel(context, ZMQ_REQ) {
		}

		void run() {
			initialize();
			communicate();
		}

	private:
		void initialize() {
			std::cout << "Connecting to hello server "<< endpoint << " ...\n";
			channel.connect("tcp://" + endpoint);
		}

		void communicate() {
			int const requestNumber = 10;
			for (int i = 1; i <= requestNumber; ++i)
				makeRequest("Hello");
		}

		void makeRequest(std::string const& text) {
			std::cout << "Sending " << text << "..."
					<< " Received: " << request(text) << std::endl;
		}

		std::string request(std::string const& text) {
			send(text);
			return receive();
		}

		void send(std::string const& text) {
			zmq::message_t request(text.size());
			::memcpy(request.data(), text.c_str(), text.size());
			channel.send(request);
		}

		std::string receive() {
			zmq::message_t reply;
			channel.recv(&reply);
			return std::string((char*)reply.data(), reply.size());
		}

	private:
		std::string endpoint;
		zmq::context_t context;
		zmq::socket_t channel;
	};
}

int main(int argc, char* argv[]) {
	std::string endpoint = "localhost:5559";
	if (argc > 1)
		endpoint = argv[1];
	zmqhello::Client client(endpoint);
	client.run();
	return 0;
}