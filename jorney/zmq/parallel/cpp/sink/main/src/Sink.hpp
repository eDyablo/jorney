#pragma once

#include "zmq.hpp"
#include <chrono>
#include <iostream>
#include <string>

namespace zmqparallel {
  class Sink {
  public:
    Sink() :
      context(1),
      sinkChannel(context, ZMQ_PULL),
      workerControlChannel(context, ZMQ_PUB) {
    }

    void communicate(std::string const& sinkEndpoint,
        std::string const& workerControlEndpoint) {
      connectSink(sinkEndpoint);
      connectWorkerControl(workerControlEndpoint);
      communicate();
    }

  private:
    void connectSink(std::string const& endpoint) {
      if (useSoloMode(endpoint))
        sinkChannel.bind("tcp://" + endpoint);
      else
        sinkChannel.connect("tcp://" + endpoint);
    }

    void connectWorkerControl(std::string const& endpoint) {
      if (useSoloMode(endpoint))
        workerControlChannel.bind("tcp://" + endpoint);
      else
        workerControlChannel.connect("tcp://" + endpoint);
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

      stopWorkers();
    }

    void stopWorkers() {
      send(workerControlChannel, "STOP");
    }

    void send(zmq::socket_t& channel, std::string const& text) {
      zmq::message_t message(text.size());
      std::copy(text.begin(), text.end(),
          stdext::make_checked_array_iterator(
                static_cast<char*>(message.data()), text.size()));
      channel.send(message);
    }

  private:
    zmq::context_t context;
    zmq::socket_t sinkChannel;
    zmq::socket_t workerControlChannel;
  };
}