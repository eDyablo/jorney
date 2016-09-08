#pragma once

#include <string>
#include "zmq.hpp"

namespace zmqbridge {
	class PubSubForwarder {
	public:
		PubSubForwarder() :
			context(1),
			frontendSocket(context, ZMQ_SUB),
			backendSocket(context, ZMQ_PUB) {
		}

		void communicate(std::string const& frontend, std::string const& backend) {
			initialize(frontend, backend);
			communicate();
		}

	private:
		void initialize(std::string const& frontend, std::string const& backend) {
			frontendSocket.connect("tcp://" + frontend);
			backendSocket.bind("tcp://" + backend);
			subscribeOnEverything();
		}

		void subscribeOnEverything() {
			 frontendSocket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
		}

		void communicate() {
			while (true)
				translateMessage();
		}

		void translateMessage() {
			zmq::message_t message;
			do {
				frontendSocket.recv(&message);
				backendSocket.send(message, message.more() ? ZMQ_SNDMORE : 0);
			} while (message.more());
		}

	private:
		zmq::context_t context;
		zmq::socket_t frontendSocket;
		zmq::socket_t backendSocket;
	};
}