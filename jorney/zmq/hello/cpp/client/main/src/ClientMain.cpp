#include <string>
#include <iostream>
#include "zmq.hpp"

namespace zmqhello {
	class Client {
	public:
		Client() : context(1), channel(context, ZMQ_REQ) {
		}

	public:
		void run() {
			initialize();
			communicate();
		}

	private:
		void initialize() {
			std::cout << "Connecting to hello world server..." << std::endl;
			channel.connect("tcp://localhost:5555");
		}

		void communicate() {
			int const requestNumber = 10;
			for (int requestIndex = 1; requestIndex <= requestNumber; ++requestIndex)
				makeRequest("Hello", requestIndex);
		}

		void makeRequest(std::string const& text, int index) {
			std::cout << "Sending " << text << " " << index << "..." << std::endl;
			std::cout << "Received " << request(text) << " " << index << std::endl;
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
		zmq::context_t context;
		zmq::socket_t channel;
	};
}

int main() {
	zmqhello::Client client;
	client.run();
	return 0;
}