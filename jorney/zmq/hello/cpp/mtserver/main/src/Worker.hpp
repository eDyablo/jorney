#pragma once

#include "shims/attribute/GetBegin.h"
#include "shims/attribute/GetSize.h"
#include "zmq.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

namespace zmqhello {
  class Worker {
  public:
    Worker(zmq::context_t& theContext):
      context(theContext),
      taskChannel(context, ZMQ_REP),
      controlChannel(context, ZMQ_SUB),
      active(false) {
      polls[0] = {taskChannel, 0, ZMQ_POLLIN, 0};
      polls[1] = {controlChannel, 0, ZMQ_POLLIN, 0};
    }

    void run() {
      connectTaskChannel();
      connectControlChannel();
      activate();
      communicate();
    }

  private:
    void connectTaskChannel() {
      taskChannel.connect("inproc://task");
    }

    void connectControlChannel() {
      controlChannel.connect("inproc://worker");
      controlChannel.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    }

    void activate() {
      active = true;
    }

    void communicate() {
      while (isActive()) {
        poll();
        process();
      }
    }

    bool isActive() const {
      return active;
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

    bool hasControlSignal() const {
      return hasMessage(polls[1]);
    }

    bool hasMessage(zmq::pollitem_t const& item) const {
      return item.revents & ZMQ_POLLIN;
    }

    std::string getWorkload() {
      return receive(taskChannel);
    }

    void handleWorkload(std::string const& request) {
      std::cout << std::this_thread::get_id() <<
          " Received: [" << request << "]" << std::flush;
      busy();
      answer("World");
    }

    void busy() {
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    void answer(std::string const& text) {
      zmq::message_t reply(text.size());
      std::copy(text.begin(), text.end(), static_cast<char*>(reply.data()));
      taskChannel.send(reply);
      std::cout << " Replied: [" << text << "]\n" << std::flush;
    }

    std::string getControlSignal() {
      return receive(controlChannel);
    }

    void handleControlSignal(std::string const& signal) {
      if (signal == "STOP")
        stop();
    }

    std::string receive(zmq::socket_t& channel) {
      zmq::message_t request;
      channel.recv(&request);
      return std::string(static_cast<char*>(request.data()), request.size());
    }

    void stop() {
      active = false;
    }

  private:
    zmq::context_t& context;
    zmq::socket_t taskChannel;
    zmq::socket_t controlChannel;
    zmq::pollitem_t polls[2];
    bool active;
  };

  void worker(zmq::context_t* context) {
    Worker worker(*context);
    worker.run();
  }
}