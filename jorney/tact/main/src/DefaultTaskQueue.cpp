#include "tact/DefaultTaskQueue.h"
#include "tact/Task.h"

namespace tact {
  void DefaultTaskQueue::AddTask(std::shared_ptr<Task> task) {
    m_Tasks.push_back(task);
  }

  std::shared_ptr<Task> DefaultTaskQueue::GetNextTask() const {
    return m_Tasks.empty() ? nullptr : m_Tasks.front();
  }

  void DefaultTaskQueue::Pop() {
    if (!m_Tasks.empty())
      m_Tasks.erase(m_Tasks.begin());
  }
}