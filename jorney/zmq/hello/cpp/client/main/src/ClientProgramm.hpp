#pragma once

#include "Client.hpp"
#include <string>
#include <vector>

namespace zmqhello {
	class ClientProgramm {
	public:
		void run(std::vector<std::string> const& args) {
			this->args = args;
			client.communicate(getServiceEndpoint(), getRequestNumber());
		}

	private:
		std::string getServiceEndpoint() const {
			return args.size() < 1 ? "localhost:5559" : args[0];
		}

		size_t getRequestNumber() const {
			return args.size() < 2 ? 10 : std::stoi(args[1]);
		}

	private:
		Client client;
		std::vector<std::string> args;
	};
}