#pragma once

#include <algorithm>

namespace ranges {
  template <typename V, size_t N>
  class sequence_range_stub_t {
  public:
    typedef V value_t;

  public:
    V const (&sequence)[N];
    size_t index;

    sequence_range_stub_t(V const (&sequence)[N]):
      sequence(sequence),
      index(0) {
    }

    bool is_open() const {
      return index < N;
    }

    V current() const {
      return sequence[index];
    }

    void advance() {
      ++index;
    }
  };

  template <typename V, size_t N>
  sequence_range_stub_t<V, N> make_range(V const (&sequence)[N]) {
    return sequence_range_stub_t<V, N>(sequence);
  }
}