#pragma once

namespace tact {
  class TaskRunner {
  public:
    virtual void Run() = 0;
    
    virtual ~TaskRunner() {};
  };
}