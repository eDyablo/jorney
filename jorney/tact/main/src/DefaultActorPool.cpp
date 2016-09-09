#include "tact/DefaultActor.h"
#include "tact/DefaultActorPool.h"

namespace tact {
  DefaultActorPool::DefaultActorPool(std::shared_ptr<TaskQueue> queue):
    m_Tasks(queue) {
  }

  bool DefaultActorPool::IsEmpty() const {
    return m_Actors.empty();
  }

  std::shared_ptr<Actor> DefaultActorPool::AddActor() {
    std::shared_ptr<Actor> actor = std::make_shared<DefaultActor>(m_Tasks);
    m_Actors.push_back(actor);
    return actor;
  }
}