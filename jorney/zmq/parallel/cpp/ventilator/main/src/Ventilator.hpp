#pragma once

#include "zmq.hpp"
#include "basics/Thread.h"
#include <cstdio>
#include <ctime>
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
      ::srand((unsigned)::time(0));
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
      startWorkload();
      loadTasks(100);
      endWorkload();
    }

    void notifySink() {
      send(sinkChannel, "0");
    }

    void send(zmq::socket_t& channel, std::string const& text) {
      zmq::message_t message(text.size());
      ::memcpy(message.data(), text.c_str(), text.size());
      channel.send(message); 
    }

    void startWorkload() {
      totalWorkload = 0;
      std::cout << "Sending tasks to workers...\n";
    }

    void loadTasks(size_t taskNumber) {
      for (size_t i = 0; i < taskNumber; ++i)
        loadTask(taskNumber);
    }

    void loadTask(size_t taskNumber) {
      int workload = getWorkLoad(taskNumber);
      totalWorkload += workload;
      zmq::message_t message(10);
      ::memset(message.data(), '\0', 10);
      ::sprintf((char*)message.data(), "%d", workload);
      std::cout << workload << " " << std::flush;
      publishingChannel.send(message);
    }

    int getWorkLoad(size_t taskNumber) const {
      return ::rand() % taskNumber + 1;
    }

    void endWorkload() {
      std::cout << "\nTotal expected cost: " << totalWorkload << " msec\n";
    }

  private:
    zmq::context_t context;
    zmq::socket_t publishingChannel;
    zmq::socket_t sinkChannel;
    int totalWorkload;
  };
}