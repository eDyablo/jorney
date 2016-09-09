#include "tact/DefaultActor.h"
#include "tact/Task.h"
#include "tact/TaskQueue.h"

namespace tact {
  DefaultActor::DefaultActor(std::weak_ptr<TaskQueue> queue):
      m_Queue(queue),
      m_State(&kInactive) {
  }

  bool DefaultActor::HasPendingTasks() const {
    return !m_Tasks.empty();
  }

  void DefaultActor::AddTask(std::shared_ptr<Task> task) {
    m_Tasks.push(task);
    Activate();
  }

  void DefaultActor::SetState(DefaultActor::State& newState) {
    m_State = &newState;
  }

  void DefaultActor::Activate() {
    m_State->Activate(*this);
  }

  void DefaultActor::Deactivate() {
    m_State->Deactivate(*this);
  }

  void DefaultActor::Execute() {
    m_State->Execute(*this);
  }

  void DefaultActor::ActivateItself() {
    ScheduleItself();
  }

  void DefaultActor::ScheduleTask() {
    if (HasPendingTasks()) {
      SchedulePendingTask();
      ScheduleItself();
    }
  }

  void DefaultActor::SchedulePendingTask() {
    std::shared_ptr<TaskQueue> queue = m_Queue.lock();
    queue->AddTask(m_Tasks.front());
    m_Tasks.pop();
  }

  void DefaultActor::ScheduleItself() {
    std::shared_ptr<TaskQueue> queue = m_Queue.lock();
    queue->AddTask(shared_from_this());
  }

  void DefaultActor::DeactivateItself() {
  }
}