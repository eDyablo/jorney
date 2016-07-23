#pragma once

namespace Turnstile {
	class Machine;

	class State {
	public:
		static State& LOCKED;
		static State& UNLOCKED;

		virtual void coin(Machine& machine) = 0;

		virtual void pass(Machine& machine) = 0;
	};
}