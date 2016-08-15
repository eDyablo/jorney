#pragma once

#include "Worker.hpp"
#include <vector>
#include <string>

namespace zmqparallel {
  class WorkerProgramm {
  public:
  	void run(std::vector<std::string> const& args) {
  		worker.communicate(getTaskEndpoint(args), getSinkEndpoint(args));
  	}

  private:
  	std::string getTaskEndpoint(std::vector<std::string> const& args) const {
  		return (args.size() < 1) ? "localhost:5557" : args[0];
  	}

  	std::string getSinkEndpoint(std::vector<std::string> const& args) const {
  		return (args.size() < 2) ? "localhost:5558" : args[1];
  	}

  private:
  	Worker worker;
  };
}