#include "tact/DefaultTaskRunner.h"
#include "tact/Task.h"
#include "tact/TaskQueue.h"

namespace tact
{
  DefaultTaskRunner::DefaultTaskRunner(std::shared_ptr<TaskQueue> queue):
    m_Queue(queue) {
  }

  void DefaultTaskRunner::Run() {
    for (std::shared_ptr<Task> task = m_Queue->GetNextTask();
      task != nullptr; task = m_Queue->GetNextTask()) {
      task->Execute();
      m_Queue->Pop();
    }
  }
}