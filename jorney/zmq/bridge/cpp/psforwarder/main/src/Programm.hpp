#pragma once

#include "Bridge.hpp"

namespace zmqbridge {
	class Programm {
	public:
		void run(std::vector<std::string> const& parameters) {
			checkParameters(parameters);
			bridge.communicate(parameters[0], parameters[1]);
		}

	private:
		void checkParameters(std::vector<std::string> const& parameters) {
			if (parameters.size() < 1)
				throw std::runtime_error("Please specify frontend and backend endpoints");
			else if (parameters.size() < 2)
				throw std::runtime_error("Please specify backend endpoint");
		}

	private:
		PubSubForwarder bridge;
	};
}