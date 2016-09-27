#pragma once

#include "zmq.hpp"

class DisplayService {
public:
  DisplayService():
    context(1) {
  }

public:
  void processRequest() {
  }

private:
  zmq::context_t context;
};