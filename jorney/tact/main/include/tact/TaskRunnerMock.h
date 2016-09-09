#pragma once

#include "gmock/gmock.h"
#include "tact/TaskRunner.h"

namespace tact {
  class TaskRunnerMock : public TaskRunner {
  public:
    MOCK_METHOD0(Run, void());
  };
}