#pragma once

#include <string>

namespace ranges {
  template <typename V>
  class single_value_range_t {
  public:
    typedef V value_t;

  public:
    single_value_range_t(value_t value):
      value(value),
      open(true) {
    }

    bool is_open() const {
      return open;
    }

    value_t current() const {
      return value;
    }

    void advance() {
      open = false;
    }

  private:
    value_t value;
    bool open;
  };

  template <typename V>
  single_value_range_t<V> value_range(const V& value) {
    return single_value_range_t<V>(value);
  }

  single_value_range_t<std::string> value_range(const char* const value) {
    return value_range(std::string(value));
  }
}