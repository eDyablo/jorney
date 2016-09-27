#pragma once

namespace ranges {
  template <typename V>
  class value_range_stub_t {
  public:
    typedef V value_t;

  public:
    value_range_stub_t(V value):
      value(value) {
    }

    V current() const {
      return value;
    }

    bool is_open() const {
      return true;
    }

    V value;
  };
}