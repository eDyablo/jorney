#pragma once

#include "zmq.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

namespace zmqparallel {
  class Worker {
  public:
    Worker() :
      context(1),
      taskChannel(context, ZMQ_PULL),
      sinkChannel(context, ZMQ_PUSH) {
    }

    void communicate(std::string const& taskEndpoint,
        std::string const& sinkEndpoint) {
      taskChannel.connect("tcp://" + taskEndpoint);
      sinkChannel.connect("tcp://" + sinkEndpoint);
      communicate();
    }

  private:
    void communicate() {
      while (true)
        doWork();
    }

    void doWork() {
      doWork(getWorkload());      
    }

    int getWorkload() {
      return std::stoi(receive(taskChannel));
    }

    std::string receive(zmq::socket_t& channel) {
      zmq::message_t message;
      channel.recv(&message);
      return std::string(static_cast<char*>(message.data()), message.size());
    }

    void doWork(int workload) {
      std::cout << workload << " ";
      std::this_thread::sleep_for(std::chrono::milliseconds(workload));
      send(sinkChannel, "");
    }

    void send(zmq::socket_t& channel, std::string const& text) {
      zmq::message_t message(text.size());
      std::copy(text.begin(), text.end(), static_cast<char*>(message.data()));
      channel.send(message);
    }

  private:
    zmq::context_t context;
    zmq::socket_t taskChannel;
    zmq::socket_t sinkChannel;
  };
}