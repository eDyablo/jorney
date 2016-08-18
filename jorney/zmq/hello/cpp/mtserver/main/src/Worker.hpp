#pragma once

#include "zmq.hpp"
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <algorithm>

namespace zmqhello {
  class Worker {
  public:
    Worker(zmq::context_t& theContext):
      context(theContext),
      channel(context, ZMQ_REP) {
    }

    void run() {
      channel.connect("inproc://workers");
      communicate();
    }

  private:
    void communicate() {
      while (true)
        handle(receive());
    }

    std::string receive() {
      zmq::message_t request;
      channel.recv(&request);
      return std::string(static_cast<char*>(request.data()), request.size());
    }

    void handle(std::string const& request) {
      std::cout << std::this_thread::get_id() <<
          " Received request: [" << request << "]\n";
      busy();
      answer("World");
    }

    void busy() {
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    void answer(std::string const& text) {
      zmq::message_t reply(text.size());
      std::copy(text.begin(), text.end(), static_cast<char*>(reply.data()));
      channel.send(reply);
    }

  private:
    zmq::context_t& context;
    zmq::socket_t channel;
  };

  void worker(zmq::context_t* context) {
    Worker worker(*context);
    worker.run();
  }
}