#pragma once

#include "zmq.hpp"
#include "basics/Thread.h"
#include <cstdio>
#include <iostream>
#include <string>

namespace zmqparallel {
  class Ventilator {
  public:
    Ventilator():
      context(1),
      publishingChannel(context, ZMQ_PUSH),
      sinkChannel(context, ZMQ_PUSH) {
    }

    void communicate(std::string const& publishingEndpoint,
        std::string const& sinkEndpoint) {
      initialize(publishingEndpoint, sinkEndpoint);
      communicate();
    }

  private:
    void initialize(std::string const& publishingEndpoint,
        std::string const& sinkEndpoint) {
      connectPublishing(publishingEndpoint);
      connectWorkers();
      connectSink(sinkEndpoint);
      ::srand((unsigned)time(0));
    }

    void connectPublishing(std::string const& endpoint) {
      if (useSoloMode(endpoint))
        publishingChannel.bind("tcp://" + endpoint);
      else
        publishingChannel.connect("tcp://" + endpoint);
    }

    bool useSoloMode(std::string const& endpoint) {
      return endpoint.find_first_of('*') == 0;
    }

    void connectWorkers() {
      std::cout << "Press Enter when the workers are ready: ";
      std::getc(stdin);
    }

    void connectSink(std::string const& endpoint) {
      sinkChannel.connect("tcp://" + endpoint);
    }

    void communicate() {
      notifySink();
      std::cout << "Sending tasks to workers...\n";
      int totalWorkload = 0;
      int const taskNumber = 100;
      for (int taskIndex = 0; taskIndex < taskNumber; ++taskIndex) {
        int workload = ::rand() % taskNumber + 1;
        totalWorkload += workload;
        zmq::message_t message(10);
        ::memset(message.data(), '\0', 10);
        ::sprintf((char*)message.data(), "%d", workload);
        std::cout << workload << " " << std::flush;
        publishingChannel.send(message);
      }
      std::cout << "\nTotal expected cost: " << totalWorkload << " msec\n";
    }

    void notifySink() {
      zmq::message_t message(2);
      ::memcpy(message.data(), "0", 1);
      sinkChannel.send(message);
    }

  private:
    zmq::context_t context;
    zmq::socket_t publishingChannel;
    zmq::socket_t sinkChannel;
  };
}