#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include "zmq.hpp"

namespace zmqweather {
	class Subscriber {
	public:
		Subscriber() :
			context(1),
			socket(context, ZMQ_SUB) {
		}

		void communicate(std::string const& endpoint) {
			connect(endpoint);
		}

		long getAverageTemperature(std::string const& zipCode, size_t number) {
			filter(zipCode);
			long total_temp = 0;
			for (int i = 0; i < number; i++) {
				zmq::message_t update;
				int zipcode, temperature, relhumidity;
				socket.recv(&update);
				std::istringstream iss(static_cast<char*>(update.data()));
				iss >> zipcode >> temperature >> relhumidity ;
				std::cout << "Got " << temperature << "F " << relhumidity << "\n";
				total_temp += temperature;		
			}
			return (long)(total_temp / number);
		}

	private:
		void connect(std::string const& endpoint) {
			socket.connect("tcp://" + endpoint);
		}

		void filter(std::string const& zipCode) {
			socket.setsockopt(ZMQ_SUBSCRIBE, zipCode.c_str(), zipCode.size());
		}

	private:
		zmq::context_t context;
		zmq::socket_t socket;
	};
}