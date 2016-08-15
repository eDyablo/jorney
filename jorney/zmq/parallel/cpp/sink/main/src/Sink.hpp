#pragma once

#include "zmq.hpp"
#include <chrono>
#include <string>
#include <iostream>

namespace zmqparallel {
  class Sink {
  public:
    Sink() :
      context(1),
      sinkChannel(context, ZMQ_PULL) {
    }

    void communicate(std::string const& sinkEndpoint) {
      connect(sinkEndpoint);
      communicate();
    }

  private:
    void connect(std::string const& sinkEndpoint) {
      if (useSoloMode(sinkEndpoint))
        sinkChannel.bind("tcp://" + sinkEndpoint);
      else
        sinkChannel.connect("tcp://" + sinkEndpoint);
    }

    bool useSoloMode(std::string const& endpoint) const {
      return endpoint.find_first_of('*') == 0;
    }

    void communicate() {
      zmq::message_t message;
      sinkChannel.recv(&message);

      auto start = std::chrono::steady_clock::now();

      int const taskNumber = 100;
      int total_msec = 0;
      for (int taskIndex = 0; taskIndex < taskNumber; taskIndex++) {
        sinkChannel.recv(&message);
        if ((taskIndex / 10) * 10 == taskIndex)
          std::cout << ":";
        else
          std::cout << ".";
      }

      auto end = std::chrono::steady_clock::now();
      auto interval = std::chrono::duration_cast<std::chrono::milliseconds>(
          end - start).count();

      std::cout << "\nCost:" << interval << " msec\n";
    }

  private:
    zmq::context_t context;
    zmq::socket_t sinkChannel;
  };
}