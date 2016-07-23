#include "gmock/gmock.h"
#include "turnstile/Machine.h"
#include "turnstile/State.h"

#include <string>

using namespace ::testing;
using namespace ::Turnstile;

class TestableMachine : public Test, public Machine {
public:
	Machine* machine;
	std::string actions;

	void SetUp() {
	 machine = this;
	}

	void unlock() {
		actions += "U";
	}

	void lock() {
		actions += "L";
	}

	void alarm() {
		actions += "A";
	}

	void thanks() {
		actions += "T";
	}
};

class LockedMachine : public TestableMachine {
public:
	void SetUp() {
		TestableMachine::SetUp();
		setState(State::LOCKED);
	}
};

TEST_F(LockedMachine, Gets_unlocked_by_a_coin) {
	machine->coin();
	ASSERT_THAT(actions, Eq("U"));
}

TEST_F(LockedMachine, Sets_alarm_if_passed) {
	machine->pass();
	ASSERT_THAT(actions, Eq("A"));
}

TEST_F(LockedMachine, Toogles_when_normally_passed) {
	machine->coin();
	machine->pass();
	ASSERT_THAT(actions, Eq("UL"));
}

class UnlockedMachine : public TestableMachine {
public:
	void SetUp() {
		TestableMachine::SetUp();
		setState(State::UNLOCKED);
	}
};

TEST_F(UnlockedMachine, Locks_after_pass) {
	machine->pass();
	ASSERT_THAT(actions, Eq("L"));
}

TEST_F(UnlockedMachine, Thanks_for_a_coin) {
	machine->coin();
	ASSERT_THAT(actions, Eq("T"));
}