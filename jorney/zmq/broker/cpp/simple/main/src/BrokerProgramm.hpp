#pragma once

#include "Broker.hpp"
#include <string>
#include <vector>

namespace zmqbroker {
	class BrokerProgramm {
	public:
		void run(std::vector<std::string> const& args) {
			this->args = args;
			broker.run(getFrontend(), getBackend());
		}

	private:
		std::string getFrontend() const {
			return args.size() < 1 ? "*:5559" : args[0];
		}

		std::string getBackend() const {
			return args.size() < 2 ? "*:5560" : args[1];
		}

	private:
		SimpleBroker broker;
		std::vector<std::string> args;
	};
}