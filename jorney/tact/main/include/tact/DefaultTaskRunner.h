#pragma once

#include "tact/TaskRunner.h"
#include <memory>

namespace tact {
  class TaskQueue;

  class DefaultTaskRunner : public TaskRunner {
  public:
    DefaultTaskRunner(std::shared_ptr<TaskQueue> queue);

    void Run() override;

  private:
    std::shared_ptr<TaskQueue> m_Queue;
  };
}