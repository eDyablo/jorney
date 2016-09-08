#include "ServerProgramm.hpp"
#include <algorithm>
#include <atomic>
#include <csignal>
#include <exception>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

namespace {
	volatile std::atomic<zmqhello::ServerProgramm*> signalHandler;
}

void signal_handler(int signal)
{
  signalHandler.load()->handleSignal(signal);
  std::signal(signal, SIG_DFL);
}

int main(int argc, char* argv[]) {
	try {
		std::vector<std::string> args;
		std::copy(&argv[1], &argv[argc], std::back_inserter(args));
		zmqhello::ServerProgramm program;
		signalHandler.store(&program);
		std::signal(SIGINT, signal_handler);
		program.run(args);
		signalHandler.store(0);
		return 0;
	}
	catch (std::exception const& e) {
		std::cout << e.what() << "\n";
		return 1;
	}
	catch (...) {
		std::cout << "Something went wrong\n";
		return 2;
	}
}