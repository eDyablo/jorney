#pragma once

#include "Ventilator.hpp"
#include <string>
#include <vector>

namespace zmqparallel {
  class VentilatorProgramm {
  public:
    void run(std::vector<std::string> const& args) {
      ventilator.communicate(getPublishingEndpoint(args),
          getSinkEndpoint(args));
    }

  private:
    std::string getPublishingEndpoint(
        std::vector<std::string> const& args) const {
      if (args.size() < 1)
        return "*:5557";
      else
        return args[0];
    }

    std::string getSinkEndpoint(
        std::vector<std::string> const& args) const {
      if (args.size() < 2)
        return "localhost:5558";
      else
        return args[1];
    }

  private:
    Ventilator ventilator;
  };
}