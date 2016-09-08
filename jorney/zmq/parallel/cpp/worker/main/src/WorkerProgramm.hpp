#pragma once

#include "Worker.hpp"
#include <vector>
#include <string>

namespace zmqparallel {
  class WorkerProgramm {
  public:
  	void run(std::vector<std::string> const& args) {
      this->args = args;
  		worker.communicate(getTaskEndpoint(), getSinkEndpoint(),
          getControlEndpoint());
  	}

  private:
  	std::string getTaskEndpoint() const {
  		return (args.size() < 1) ? "localhost:5557" : args[0];
  	}

  	std::string getSinkEndpoint() const {
  		return (args.size() < 2) ? "localhost:5558" : args[1];
  	}

    std::string getControlEndpoint() const {
      return args.size() < 3 ? "localhost:5559" : args[2];
    }

  private:
  	Worker worker;
    std::vector<std::string> args;
  };
}