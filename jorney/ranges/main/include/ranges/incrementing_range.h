#pragma once

namespace ranges {
  template <typename V>
  class incrementing_range_t {
  public:
    typedef V value_t;

  public:
    incrementing_range_t(value_t begin)
      : value(begin) {
    }

    bool is_open() const {
      return true;
    }

    value_t current() const {
      return value;
    }

    void advance() {
      ++value;
    }

  private:
    value_t value;
  };
}