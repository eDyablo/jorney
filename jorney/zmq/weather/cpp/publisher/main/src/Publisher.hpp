#pragma once

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>

#include "basics/Thread.h"
#include "zmq.hpp"

namespace zmqweather {
	class Publisher {
	public:
		Publisher() :
			context(1),
			pubSocket(context, ZMQ_PUB) {
		}

		void communicate(std::string const& endpoint) {
			initilaize(endpoint);
			communicate();
		}

	private:
		void initilaize(std::string const& endpoint) {
			connect(endpoint);
			initilaizeWeatherData();
		}

		void connect(std::string const& endpoint) {
			if (useSoloMode(endpoint))
				pubSocket.bind("tcp://" + endpoint);
			else
				pubSocket.connect("tcp://" + endpoint);
		}

		bool useSoloMode(std::string const& endpoint) const {
			return endpoint.find_first_of('*') == 0;
		}

		void initilaizeWeatherData() {
			::srand((unsigned)::time(0));
		}

		void communicate() {
			while (true)
				publishWeatherData();
		}

		void publishWeatherData() {
			std::string const data = getData();
			publish(data);
			std::cout << data << "\n";
			basics::msleep(50);
		}

		int getZipCode() const {
			return ::rand() % 10 + 10000;
		}

		int getTemperature() const {
			return ::rand() % 215 - 80;
		}

		int getHumidity() const {
			return ::rand() % 50 + 10;
		}

		std::string getData() const {
			std::stringstream data;
			data << getZipCode() << " " << getTemperature() << " " << getHumidity();
			return data.str();
		}

		void publish(std::string const& text) {
			zmq::message_t message(text.size());
			std::copy(text.begin(), text.end(),
					reinterpret_cast<char*>(message.data()));
			pubSocket.send(message);
		}

	private:
		zmq::context_t context;
		zmq::socket_t pubSocket;
	};
}