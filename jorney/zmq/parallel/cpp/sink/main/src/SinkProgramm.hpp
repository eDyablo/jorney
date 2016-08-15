#pragma once

#include "Sink.hpp"
#include <string>
#include <vector>

namespace zmqparallel {
	class SinkProgramm {
	public:
		void run(std::vector<std::string> const& args) {
			sink.communicate(getSinkEndpoint(args));
		}

	private:
		std::string getSinkEndpoint(std::vector<std::string> const& args) {
			return args.size() < 1 ? "*:5558" : args[0];
		}

	private:
		Sink sink;
	};
}