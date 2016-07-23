#pragma once

namespace Turnstile {
	class State;

	class Machine {
		State* state;

	public:
		void setState(State& state);

		void coin();

		void pass();

		virtual void unlock() = 0;

		virtual void lock() = 0;

		virtual void alarm() = 0;

		virtual void thanks() = 0;
	};
}