#include <iostream>
#include <sstream>

#include "zmq.hpp"

int main() {
	zmq::context_t context(1);
	std::cout << "Collecting updates from weather server..." << std::endl;
	zmq::socket_t subscriber(context, ZMQ_SUB);
	subscriber.connect("tcp://localhost:5556");
	const char* filter = "10001 ";
	subscriber.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));
	int update_nbr;
	long total_temp = 0;
	for (update_nbr = 0; update_nbr < 100; update_nbr++) {
		zmq::message_t update;
		int zipcode, temperature, relhumidity;
		subscriber.recv(&update);
		std::istringstream iss(static_cast<char*>(update.data()));
		iss >> zipcode >> temperature >> relhumidity ;
		std::cout << "Got " << (int)(temperature / relhumidity) << "F\n";
		total_temp += temperature;		
	}
	std::cout	<< "Average temperature for zipcode '" << filter
			<< "' was " << (int)(total_temp / update_nbr) << "F"
			<< std::endl;
	return 0;
}