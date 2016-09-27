#pragma once

namespace ranges {
  template <typename V>
  class closed_range_stub_t {
  public:
    typedef V value_t;

  public:
    bool is_open() const {
      return false;
    }

    V current() const {
      return V();
    }

    void advance() {
    }
  };
}