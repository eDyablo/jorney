#pragma once

#include "Sink.hpp"
#include <string>
#include <vector>

namespace zmqparallel {
	class SinkProgramm {
	public:
		void run(std::vector<std::string> const& args) {
			this->args = args;
			sink.communicate(getSinkEndpoint(), getWorkerControlEndpoint());
		}

	private:
		std::string getSinkEndpoint() const {
			return args.size() < 1 ? "*:5558" : args[0];
		}

		std::string getWorkerControlEndpoint() const {
			return args.size() < 2 ? "*:5559" : args[1];
		}

	private:
		Sink sink;
		std::vector<std::string> args;
	};
}