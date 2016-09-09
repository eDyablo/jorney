#include "gmock/gmock.h"
#include "tact/Actor.h"
#include "tact/DefaultActorPool.h"
#include "tact/TaskQueueMock.h"

using namespace ::testing;
using namespace ::tact;

class NewPool : public Test {
protected:
  NewPool():
    m_Tasks(std::make_shared<TaskQueueMock>()),
    m_Pool(m_Tasks) {
  }

protected:
  std::shared_ptr<TaskQueueMock> m_Tasks;
  DefaultActorPool m_Pool;
};

TEST_F(NewPool, IsEmpty_NoActorAdded_ReturnsTrue) {
  ASSERT_THAT(m_Pool.IsEmpty(), Eq(true));
}

TEST_F(NewPool, IsEmpty_OneActorAdded_ReturnsFalse) {
  m_Pool.AddActor();
  ASSERT_THAT(m_Pool.IsEmpty(), Eq(false));
}

TEST_F(NewPool, AddActor_NoParameters_ReturnsActor) {
  ASSERT_THAT(m_Pool.AddActor(), NotNull());
}