#pragma once

#include "Worker.hpp"
#include "zmq.hpp"
#include <algorithm>
#include <string>
#include <thread>
#include <vector>

namespace zmqhello {
  class Server {
  public:
    Server() :
      context(1),
      clientChannel(context, ZMQ_ROUTER),
      taskChannel(context, ZMQ_DEALER),
      workerControlChannel(context, ZMQ_PUB),
      proxyControlChannel(context, ZMQ_PUB) {
    }

    void communicate(std::string const& endPoint, size_t workersNumber) {
      connect(endPoint);
      startWorkers(workersNumber);
      communicate();
    }

    void stop() {
      stopWorkers();
      commandProxy("TERMINATE");
    }

  private:
    void connect(std::string const& endPoint) {
      connectClientChannel(endPoint);
      connectWorkerChannel();
      connectProxyControlChannel();
    }

    void connectClientChannel(std::string const& endPoint) {
      if (useSoloMode(endPoint))
        clientChannel.bind("tcp://" + endPoint);
      else
        clientChannel.connect("tcp://" + endPoint);
    }

    bool useSoloMode(std::string const& endPoint) const {
      return endPoint.find_first_of('*') == 0;
    }

    void connectWorkerChannel() {
      taskChannel.bind("inproc://task");
      workerControlChannel.bind("inproc://worker");
    }

    void connectProxyControlChannel() {
      proxyControlChannel.bind("inproc://proxy");
    }

    void startWorkers(size_t number) {
      for (size_t i = 0; i < number; ++i)
        startWorker();
    }

    void startWorker() {
      workers.push_back(std::thread(worker, &context));
    }

    void communicate() {
      zmq::socket_t control(context, ZMQ_SUB);
      control.setsockopt(ZMQ_SUBSCRIBE, "", 0);
      control.connect("inproc://proxy");
      zmq::proxy_steerable(clientChannel, taskChannel, 0, control);
    }

    void commandWorkers(std::string const& command) {
      send(workerControlChannel, command);
    }

    void commandProxy(std::string const& command) {
      send(proxyControlChannel, command);
    }

    void send(zmq::socket_t& channel, std::string const& text) {
      zmq::message_t message(text.size());
      std::copy(text.begin(), text.end(),
          stdext::make_checked_array_iterator(
              static_cast<char*>(message.data()), text.size()));
      channel.send(message);
    }

    void stopWorkers() {
      commandWorkers("STOP");
      for (auto i = workers.begin(); i != workers.end(); ++i)
        (*i).join();
    }

  private:
    zmq::context_t context;
    zmq::socket_t clientChannel;
    zmq::socket_t taskChannel;
    zmq::socket_t workerControlChannel;
    zmq::socket_t proxyControlChannel;
    std::vector<std::thread> workers;
  };
}