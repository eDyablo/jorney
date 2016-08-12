#pragma once

#include "Server.hpp"

#include <vector>
#include <string>

namespace zmqhello {
	class ServerProgramm {
	public:
		void run(std::vector<std::string> const& args) {
			server.communicate(getEndPoint(args), getWorkersNumber(args));
		}

	private:
		std::string getEndPoint(std::vector<std::string> const& args) {
			if (args.empty())
				return "*:5555";
			else
				return args[0];
		}

		size_t getWorkersNumber(std::vector<std::string> const& args) {
			if (args.size() < 2)
				return 5;
			else
				return std::stoi(args[1]);
		}

	private:
		Server server;
	};
}