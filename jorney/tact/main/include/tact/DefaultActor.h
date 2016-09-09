#pragma once

#include "tact/Actor.h"
#include "tact/Task.h"
#include <memory>
#include <queue>

namespace tact {
  class TaskQueue;

  class DefaultActor : public Actor, public Task,
    public std::enable_shared_from_this<Task> {
  public:
    class State;

    DefaultActor(std::weak_ptr<TaskQueue> queue);

    bool HasPendingTasks() const override;

    void AddTask(std::shared_ptr<Task> task) override;

    void Activate() override;

    void Deactivate() override;

    void Execute() override;

    void SetState(State& newState);

    virtual void ActivateItself();

    virtual void DeactivateItself();

    virtual void ScheduleTask();

  private:
    void SchedulePendingTask();

    void ScheduleItself();

  public:
    static State& kActive;
    static State& kInactive;

  private:
    std::weak_ptr<TaskQueue> m_Queue;
    std::queue<std::shared_ptr<Task>> m_Tasks;
    State* m_State;
  };

  class DefaultActor::State {
  public:
    virtual void Activate(DefaultActor& actor) = 0;

    virtual void Deactivate(DefaultActor& actor) = 0;

    virtual void Execute(DefaultActor& actor) = 0;
  };
}