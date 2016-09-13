#pragma once

#include <vector>

namespace ranges {
  template <typename R>
  std::vector<typename R::value_t> make_vector(R range) {
    std::vector<R::value_t> vector;
    for (; range.is_open(); range.advance())
      vector.push_back(range.current());
    return vector;
  }
}