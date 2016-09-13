#pragma once

#include <exception>

namespace ranges {
  class empty_range_exception : public std::exception {
  };
}