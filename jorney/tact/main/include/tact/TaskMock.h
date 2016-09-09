#pragma once

#include "tact/Task.h"
#include "gmock/gmock.h"

namespace tact {
  class TaskMock : public Task {
  public:
    MOCK_METHOD0(Execute, void());
  };
}