#pragma once

namespace ranges {
  template <typename V>
  class open_range_stub_t {
  public:
    typedef V value_t;

  public:
    bool is_open() const {
      return true;
    }

    V current() const {
      return V();
    }

    void advance() {
    }
  };
}