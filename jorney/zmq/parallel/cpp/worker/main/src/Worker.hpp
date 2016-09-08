#pragma once

#include "shims/attribute/GetBegin.h"
#include "shims/attribute/GetSize.h"
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
      sinkChannel(context, ZMQ_PUSH),
      controlChannel(context, ZMQ_SUB) {
      polls[0] = {taskChannel, 0, ZMQ_POLLIN, 0};
      polls[1] = {controlChannel, 0, ZMQ_POLLIN, 0};
    }

    void communicate(std::string const& taskEndpoint,
        std::string const& sinkEndpoint, std::string const& controlEndpoint) {
      connectTaskSource(taskEndpoint);
      connectSink(sinkEndpoint);
      connectController(controlEndpoint);
      communicate();
    }

  private:
    void connectTaskSource(std::string const& endpoint) {
      taskChannel.connect("tcp://" + endpoint);
    }

    void connectSink(std::string const& endpoint) {
      sinkChannel.connect("tcp://" + endpoint);
    }

    void connectController(std::string const& endpoint) {
      controlChannel.connect("tcp://" + endpoint);
      controlChannel.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    }

    void communicate() {
      while (true) {
        poll();
        process();
      }
    }

    void poll() {
      using namespace shims;
      zmq::poll(GetBegin(polls), GetSize(polls), -1);
    }

    void process() {
      if (hasWorkload())
        handleWorkload(getWorkload());
      if (hasControlSignal())
        handleControlSignal(getControlSignal());
    }

    bool hasWorkload() const {
      return hasMessage(polls[0]);
    }

    int getWorkload() {
      return std::stoi(receive(taskChannel));
    }

    void handleWorkload(int workload) {
      std::cout << workload << " ";
      std::this_thread::sleep_for(std::chrono::milliseconds(workload));
      send(sinkChannel, "");
    }

    bool hasControlSignal() const {
      return hasMessage(polls[1]);
    }

    std::string getControlSignal() {
      return receive(controlChannel);
    }

    void handleControlSignal(std::string const& signal) {
      std::cout << "Control signal [" << signal << "] received\n";
      if (signal == "STOP")
        stop();
    }

    void stop() {
      ::exit(0);
    }

    bool hasMessage(zmq::pollitem_t const& item) const {
      return item.revents & ZMQ_POLLIN;
    }

    std::string receive(zmq::socket_t& channel) {
      zmq::message_t message;
      channel.recv(&message);
      return std::string(static_cast<char*>(message.data()), message.size());
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
    zmq::socket_t taskChannel;
    zmq::socket_t sinkChannel;
    zmq::socket_t controlChannel;
    zmq::pollitem_t polls[2];
  };
}