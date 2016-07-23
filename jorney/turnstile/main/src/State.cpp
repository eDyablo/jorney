#include "turnstile/State.h"
#include "turnstile/Machine.h"

namespace Turnstile {
	class LockedState : public State {
		void coin(Machine& machine) {
			machine.setState(UNLOCKED);
			machine.unlock();
		}

		void pass(Machine& machine) {
			machine.alarm();
		}
	} locked;

	class UnlockedState : public State {
		void coin(Machine& machine) {
			machine.thanks();
		}

		void pass(Machine& machine) {
			machine.setState(LOCKED);
			machine.lock();
		}
	} unlocked;

	State& State::LOCKED = locked;
	State& State::UNLOCKED = unlocked;
}