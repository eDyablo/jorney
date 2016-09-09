#pragma once

#include "tact/TaskQueue.h"
#include <vector>

namespace tact {
  class Task;

  class DefaultTaskQueue : public TaskQueue {
  public:
    void AddTask(std::shared_ptr<Task> task) override;

    std::shared_ptr<Task> GetNextTask() const override;

    void Pop() override;

  private:
    std::vector<std::shared_ptr<Task>> m_Tasks;
  };
}