#pragma once

#include "gmock/gmock.h"
#include "tact/TaskQueue.h"

namespace tact {
  class TaskQueueMock : public TaskQueue {
  public:
    MOCK_METHOD1(AddTask, void(std::shared_ptr<Task>));
    MOCK_CONST_METHOD0(GetNextTask, std::shared_ptr<Task>());
    MOCK_METHOD0(Pop, void());
  };
}