#include <ctime>
#include <cstdlib>
#include <iostream>

#include "zmq.hpp"
#include "basics/Thread.h"

int main() {
	zmq::context_t context(1);
	zmq::socket_t publisher(context, ZMQ_PUB);
	publisher.bind("tcp://*:5556");
	srand((unsigned)time(0));
	while (true) {
		int zipcode, temperature, relhumidity;
		zipcode = ::rand() % 10 + 10000;
		temperature = ::rand() % 215 - 80;
		relhumidity = ::rand() % 50 + 10;
		zmq::message_t message(20);
		snprintf((char *) message.data(), 20 ,
				"%05d %d %d", zipcode, temperature, relhumidity);
		publisher.send(message);
		std::cout << zipcode << " " << temperature << " " << relhumidity << "\n";
		basics::msleep(50);
	}
	return 0;
}