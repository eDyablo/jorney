#pragma once

#include "Publisher.hpp"

namespace zmqweather {
	class PublisherProgramm {
	public:
		void run(std::vector<std::string> const& args) {
			publisher.communicate(getEndpoint(args));
		}

	private:
		std::string getEndpoint(std::vector<std::string> const& args) const {
			if (args.empty())
				return "*:5556";
			else
				return args[0];
		}

	private:
		Publisher publisher;
	};
}