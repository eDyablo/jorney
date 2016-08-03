#include <iostream>
#include <cstdio>
#include <ctime>
#include "zmq.hpp"
#include "basics/Thread.h"

int main() {
  zmq::context_t context (1);
  zmq::socket_t sender(context, ZMQ_PUSH);
  sender.bind("tcp://*:5557");
  std::cout << "Press Enter when the workers are ready: " << std::endl;
  std::getc(stdin);
  std::cout << "Sending tasks to workers..." << std::endl;
  zmq::socket_t sink(context, ZMQ_PUSH);
  sink.connect("tcp://localhost:5558");
  zmq::message_t message(2);
  memcpy(message.data(), "0", 1);
  sink.send(message);
  srand((unsigned)time(0));
  int totalWorkload = 0;
  int const taskNumber = 100;
  for (int taskIndex = 0; taskIndex < taskNumber; ++taskIndex) {
    int workload = ::rand() % taskNumber + 1;
    totalWorkload += workload;
    message.rebuild(10);
    memset(message.data(), '\0', 10);
    sprintf ((char*)message.data(), "%d", workload);
    std::cout << workload << "\n";
    sender.send(message);
  }
  std::cout << "Total expected cost: " << totalWorkload << " msec" << std::endl;
  basics::sleep(1);
  return 0;
}