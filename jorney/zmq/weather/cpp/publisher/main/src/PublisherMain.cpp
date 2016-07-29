#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "zmq.hpp"

#define within(num) (int)((float)num * rand() / (RAND_MAX + 1.0))

int main() {
	zmq::context_t context(1);
	zmq::socket_t publisher(context, ZMQ_PUB);
	publisher.bind("tcp://*:5556");
	srand((unsigned)time(0));
	while (true) {
		int zipcode, temperature, relhumidity;
		zipcode = within(100000);
		temperature = within(215) - 80;
		relhumidity = within(50) + 10;
		zmq::message_t message(20);
		snprintf ((char *) message.data(), 20 ,
				"%05d %d %d", zipcode, temperature, relhumidity);
		publisher.send(message);
	}
	return 0;
}