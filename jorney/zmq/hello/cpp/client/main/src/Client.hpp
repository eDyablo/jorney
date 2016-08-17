#pragma once

#include "zmq.hpp"
#include <iostream>
#include <string>

namespace zmqhello {
  class Client {
  public:
    Client() :
      context(1),
      serviceChannel(context, ZMQ_REQ) {
    }

    void communicate(std::string const& serviceEndpoint, size_t requestNumber) {
      connect(serviceEndpoint);
      communicate(requestNumber);
    }

  private:
    void connect(std::string const& serviceEndpoint) {
      std::cout << "Connecting to hello server " << serviceEndpoint << " ...\n";
      serviceChannel.connect("tcp://" + serviceEndpoint);
    }

    void communicate(size_t requestNumber) {
      for (int i = 0; i < requestNumber; ++i) {
        std::cout << i + 1 << ": ";
        makeRequest("Hello");
      }
    }

    void makeRequest(std::string const& text) {
      std::cout << "Sending [" << text << "] ...";
      std::string const reply = request(text);
      std::cout << " Received: [" << reply << "]\n";
    }

    std::string request(std::string const& text) {
      send(text);
      return receive();
    }

    void send(std::string const& text) {
      zmq::message_t request(text.size());
      ::memcpy(request.data(), text.c_str(), text.size());
      serviceChannel.send(request);
    }

    std::string receive() {
      zmq::message_t reply;
      serviceChannel.recv(&reply);
      return std::string((char*)reply.data(), reply.size());
    }

  private:
    zmq::context_t context;
    zmq::socket_t serviceChannel;
  };
}