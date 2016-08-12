#pragma once

#include "zmq.hpp"
#include "Worker.hpp"

#include <string>
#include <thread>

namespace zmqhello {
	class Server {
	public:
		Server() :
			context(1),
			clients(context, ZMQ_ROUTER),
			workers(context, ZMQ_DEALER) {
		}

		void communicate(std::string const& endPoint, size_t workersNumber) {
			connect(endPoint);
			startWorkers(workersNumber);
			communicate();
		}

	private:
		void connect(std::string const& endPoint) {
			connectClients(endPoint);
			connectWorkers();
		}

		void connectClients(std::string const& endPoint) {
			if (useSoloMode(endPoint))
				clients.bind("tcp://" + endPoint);
			else
				clients.connect("tcp://" + endPoint);
		}

		bool useSoloMode(std::string const& endPoint) const {
			return endPoint.find_first_of('*') == 0;
		}

		void connectWorkers() {
			workers.bind ("inproc://workers");
		}

		void startWorkers(size_t number) {
			for (size_t i = 0; i < number; ++i)
				startWorker();
		}

		void startWorker() {
			std::thread* wt = new std::thread(worker, &context);
		}

		void communicate() {
			zmq::proxy(clients, workers, 0);
		}

	private:
		zmq::context_t context;
		zmq::socket_t clients;
		zmq::socket_t workers;
	};
}