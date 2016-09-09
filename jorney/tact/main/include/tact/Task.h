#pragma once

namespace tact {
  class Task {
  public:
    virtual void Execute() = 0;
    
    virtual ~Task() {}
  };
}