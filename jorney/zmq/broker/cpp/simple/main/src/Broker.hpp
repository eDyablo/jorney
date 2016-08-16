#pragma once

#include "zmq.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace zmqbroker {
  class SimpleBroker {
  public:
    SimpleBroker() :
      context(1),
      clientChannel(context, ZMQ_ROUTER),
      serviceChannel(context, ZMQ_DEALER) {
      items[0] = pollin(clientChannel);
      items[1] = pollin(serviceChannel);
    }

    void run(std::string const& frontend, std::string const& backend) {
      initialize(frontend, backend);
      communicate();
    }

  private:
    static zmq::pollitem_t pollin(zmq::socket_t& socket) {
      zmq::pollitem_t item = { socket, 0, ZMQ_POLLIN, 0 };
      return item;
    }

    void initialize(std::string const& frontend, std::string const& backend) {
      connectChannel(clientChannel, frontend);
      connectChannel(serviceChannel, backend);
      std::cout << "Broker's frontend is " << frontend
          << " and backend is " << backend << "\n";
    }

    void connectChannel(zmq::socket_t& channel, std::string const& endpoint) {
      if (useSoloMode(endpoint))
        channel.bind("tcp://" + endpoint);
      else
        channel.connect("tcp://" + endpoint);
    }

    bool useSoloMode(std::string const& endpoint) const {
      return endpoint.find_first_of('*') == 0;
    }

    void communicate() {
      while (true) {
        poll();
        process();
      }
    }

    void poll() {
      zmq::poll(&items[0], 2, -1);
    }

    void process() {
      processClient();
      processService();
    }

    void processClient() {
      if (hasMessage(items[0])) {
        std::cout << "client:";
        translateMessage(clientChannel, serviceChannel);
      }
    }

    void processService() {
      if (hasMessage(items[1])) {
        std::cout << "service:";
        translateMessage(serviceChannel, clientChannel);
      }
    }

    bool hasMessage(zmq::pollitem_t const& item) const {
      return item.revents & ZMQ_POLLIN;
    }

    void translateMessage(zmq::socket_t& from, zmq::socket_t& to) {
      zmq::message_t message;
      do {
        from.recv(&message);
        std::cout << "[" << std::string(static_cast<char*>(message.data()),
            message.size()) << "]\n";
        to.send(message, message.more() ? ZMQ_SNDMORE : 0);
      } while (message.more());
    }

  private:
    zmq::context_t context;
    zmq::socket_t clientChannel;
    zmq::socket_t serviceChannel;
    zmq::pollitem_t items[2];
  };
}