#include "gmock/gmock.h"
#include "tact/DefaultTaskRunner.h"
#include "tact/TaskMock.h"
#include "tact/TaskQueueMock.h"
#include <exception>
#include <vector>

using namespace ::testing;
using namespace ::tact;

class NewRunner : public Test {
protected:
  NewRunner():
    m_Queue(std::make_shared<NiceMock<TaskQueueMock>>()),
    m_Runner(m_Queue) {
    ON_CALL(*m_Queue, GetNextTask()).WillByDefault(Return(nullptr));
  }

protected:
  std::shared_ptr<TaskQueueMock> m_Queue;
  DefaultTaskRunner m_Runner;
};

TEST_F(NewRunner, Run_WithEmptyQueue_DoesNothing) {
  EXPECT_CALL(*m_Queue, GetNextTask()).WillOnce(Return(nullptr));
  ASSERT_NO_THROW(m_Runner.Run());
}

TEST_F(NewRunner, Run_WithOneTaskInQueue_ExecutesTheTaskAndPopsIt) {
  std::shared_ptr<TaskMock> task = std::make_shared<TaskMock>();
  EXPECT_CALL(*m_Queue, GetNextTask())
    .WillOnce(Return(task))
    .WillOnce(Return(nullptr));
  EXPECT_CALL(*task, Execute());
  EXPECT_CALL(*m_Queue, Pop());
  m_Runner.Run();
}

TEST_F(NewRunner, Run_QueueWithOneTaskThatThrowsOnExecute_DontCallPopOnQueueAndThrows) {
  std::shared_ptr<TaskMock> task = std::make_shared<TaskMock>();
  EXPECT_CALL(*m_Queue, GetNextTask()).WillOnce(Return(task));
  EXPECT_CALL(*task, Execute()).WillOnce(Throw(std::exception()));
  EXPECT_CALL(*m_Queue, Pop()).Times(Exactly(0));
  ASSERT_THROW(m_Runner.Run(), std::exception);
}

TEST_F(NewRunner, Run_QueueWithTwoTasks_ExecutesTasksInDirectOrder) {
  std::vector<std::shared_ptr<Task>> executed;
  std::shared_ptr<TaskMock> firstTask = std::make_shared<TaskMock>();
  std::shared_ptr<TaskMock> secondTask = std::make_shared<TaskMock>();
  EXPECT_CALL(*m_Queue, GetNextTask())
    .WillOnce(Return(firstTask))
    .WillOnce(Return(secondTask))
    .WillOnce(Return(nullptr));
  EXPECT_CALL(*secondTask, Execute())
    .After(EXPECT_CALL(*firstTask, Execute()));
  m_Runner.Run();
}