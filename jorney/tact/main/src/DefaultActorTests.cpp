#include "gmock/gmock.h"
#include "tact/DefaultActor.h"
#include "tact/TaskMock.h"
#include "tact/TaskQueueMock.h"
#include <string>

using namespace ::testing;
using namespace ::tact;

class NewActor : public Test {
protected:
  void SetUp() {
    m_Queue = std::make_shared<NiceMock<TaskQueueMock>>();
    m_Actor = std::make_shared<DefaultActor>(m_Queue);
  }
  
protected:
  std::shared_ptr<TaskQueueMock> m_Queue;
  std::shared_ptr<DefaultActor> m_Actor;
};

TEST_F(NewActor, HasPendingTasks_NoTaskAdded_ReturnsFalse) {
  ASSERT_THAT(m_Actor->HasPendingTasks(), Eq(false));
}

TEST_F(NewActor, HasPendingTasks_OneTaskAdded_ReturnsTrue) {
  m_Actor->AddTask(std::shared_ptr<Task>());
  ASSERT_THAT(m_Actor->HasPendingTasks(), Eq(true));
}

TEST_F(NewActor, ActivateItself_AddsItselfToQueue) {
  EXPECT_CALL(*m_Queue, AddTask(Eq(m_Actor)));
  m_Actor->ActivateItself();
}

TEST_F(NewActor, ScheduleTask_OneTaskAdded_MovesTheTaskToQueueAndAddsItself) {
  std::shared_ptr<Task> task = std::make_shared<TaskMock>();
  m_Actor->AddTask(task);
  EXPECT_CALL(*m_Queue, AddTask(Eq(task)));
  EXPECT_CALL(*m_Queue, AddTask(Eq(m_Actor)));
  m_Actor->ScheduleTask();
  ASSERT_THAT(m_Actor->HasPendingTasks(), Eq(false));
}

TEST_F(NewActor, Activate_DoesNotThrow) {
  EXPECT_CALL(*m_Queue, AddTask(_));
  ASSERT_NO_THROW(m_Actor->Activate());
}

TEST_F(NewActor, ScheduleTask_NoTaskAdded_DoesNotAddAnyTask) {
  EXPECT_CALL(*m_Queue, AddTask(_)).Times(Exactly(0));
  m_Actor->ScheduleTask();
}

class TestableDefaultActor : public DefaultActor, public Test {
public:
  std::string m_Actions;

  TestableDefaultActor():
    DefaultActor(std::make_shared<TaskQueueMock>()) {
  }

  void ActivateItself() override {
    m_Actions += "Activate";
  }

  void DeactivateItself() override {
    m_Actions += "Deactivate";
  }

  void ScheduleTask() override {
    m_Actions += "Schedule";
  }
};

TEST_F(TestableDefaultActor, Activate_InactiveState_ActivatesItself) {
  SetState(DefaultActor::kInactive);
  Activate();
  ASSERT_THAT(m_Actions, StrEq("Activate"));
}

TEST_F(TestableDefaultActor, Activate_ActiveState_DoesNothing) {
  SetState(DefaultActor::kActive);
  Activate();
  ASSERT_THAT(m_Actions, StrEq(""));
}

TEST_F(TestableDefaultActor, ActivateTwice_InactiveState_ActivatesItdelfOnce) {
  SetState(DefaultActor::kInactive);
  Activate();
  Activate();
  ASSERT_THAT(m_Actions, StrEq("Activate"));
}

TEST_F(TestableDefaultActor, Deactivate_ActiveState_DeactivatesItself) {
  SetState(DefaultActor::kActive);
  Deactivate();
  ASSERT_THAT(m_Actions, StrEq("Deactivate"));
}

TEST_F(TestableDefaultActor, Deactivate_InactiveState_DoesNothing) {
  SetState(DefaultActor::kInactive);
  Deactivate();
  ASSERT_THAT(m_Actions, StrEq(""));
}

TEST_F(TestableDefaultActor, DeactivateTwice_ActiveState_DeactivatesItselfOnce) {
  SetState(DefaultActor::kActive);
  Deactivate();
  Deactivate();
  ASSERT_THAT(m_Actions, StrEq("Deactivate"));
}

TEST_F(TestableDefaultActor, Execute_ActiveState_SchedulesTask) {
  SetState(DefaultActor::kActive);
  Execute();
  ASSERT_THAT(m_Actions, StrEq("Schedule"));
}

TEST_F(TestableDefaultActor, Execute_InactiveState_DoesNothing) {
  SetState(DefaultActor::kInactive);
  Execute();
  ASSERT_THAT(m_Actions, StrEq(""));
}

TEST_F(TestableDefaultActor, AddTask_NoTasksAdded_ActivatesActor) {
  AddTask(std::make_shared<TaskMock>());
  ASSERT_THAT(m_Actions, StrEq("Activate"));
}