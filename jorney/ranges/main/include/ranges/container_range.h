#pragma once

#include <algorithm>

namespace ranges {
  template <typename C>
  class container_range_t {
  public:
    typedef C container_t;
    typedef typename container_t::value_type value_t;
    typedef typename container_t::const_iterator iterator_t;

  public:
    container_range_t(container_t const& container):
      iterator(container.begin()),
      end(container.end()) {
    }

    bool is_open() const {
      return iterator != end;
    }

    value_t current() const {
      return *iterator;
    }

    void advance() {
      ++iterator;
    }

  private:
    iterator_t iterator;
    iterator_t end;
  };

  template <typename C>
  container_range_t<C> container_range(C const& container) {
    return container_range_t<C>(container);
  }
}