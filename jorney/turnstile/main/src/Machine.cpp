#include "turnstile/Machine.h"
#include "turnstile/State.h"

namespace Turnstile {
	void Machine::setState(State& state) {
		this->state = &state;
	}

	void Machine::coin() {
		state->coin(*this);
	}

	void Machine::pass() {
		state->pass(*this);
	}
}