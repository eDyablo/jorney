#pragma once

#include "ranges/empty_range_exception.h"

namespace ranges {
  template <typename V>
  class empty_range_t {
  public:
    typedef V value_t;

  public:
    bool is_open() const {
      return false;
    }

    value_t current() const {
      throw empty_range_exception();
    }

    void advance() {
    }
  };
}