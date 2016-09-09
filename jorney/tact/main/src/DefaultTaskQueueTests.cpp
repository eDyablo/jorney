#include "gmock/gmock.h"
#include "tact/DefaultTaskQueue.h"
#include "tact/TaskMock.h"

using namespace ::testing;
using namespace ::tact;

class NewQueue : public Test {
protected:
  DefaultTaskQueue m_Queue;
};

TEST_F(NewQueue, IsEmpty_NoTaskAdded_ReturnsTrue) {
  ASSERT_THAT(m_Queue.IsEmpty(), Eq(true));
}

TEST_F(NewQueue, IsEmpty_OneTaskAdded_ReturnsFalse) {
  m_Queue.AddTask(std::make_shared<TaskMock>());
  ASSERT_THAT(m_Queue.IsEmpty(), Eq(false));
}

TEST_F(NewQueue, IsEmpty_AddAndPopTask_ReturnsFalse) {
  m_Queue.AddTask(std::make_shared<TaskMock>());
  m_Queue.Pop();
  ASSERT_THAT(m_Queue.IsEmpty(), Eq(true));
}

TEST_F(NewQueue, Pop_FromEmptyQueue_DoesNothing) {
  ASSERT_NO_THROW(m_Queue.Pop());
}