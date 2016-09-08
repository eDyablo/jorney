#pragma once

#include <iostream>
#include "Subscriber.hpp"

namespace zmqweather {
	class SubscriberProgramm {
		public:
		void run(std::vector<std::string> const& args) {
			subscriber.communicate(getEndpoint(args));
			char const* zipCode = "10001";
			std::cout << "Collecting updates from weather server for '" <<
					zipCode << "' ...\n";
			long temperature = subscriber.getAverageTemperature(zipCode, 100);
			std::cout	<< "Average temperature for zipcode '" << zipCode <<
					"' was " << temperature << "F\n";
		}

	private:
		std::string getEndpoint(std::vector<std::string> const& args) const {
			if (args.empty())
				return "localhost:5556";
			else
				return args[0];
		}

	private:
		Subscriber subscriber;
	};
}