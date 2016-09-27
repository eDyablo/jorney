#pragma once

namespace ranges {
  template <typename V, typename M, typename IR>
  class mapped_range {
  public:
    typedef V value_t;
    typedef M mapper_t;
    typedef IR input_range_t;

  public:
    mapped_range(mapper_t mapper, input_range_t input):
      mapper(mapper),
      input(input) {
    }

    bool is_open() const {
      return input.is_open();
    }

    value_t current() const {
      return mapper(input.current());
    }

    void advance() {
      input.advance();
    }

  private:
    mapper_t mapper;
    input_range_t input;
  };

  template <typename V, typename M, typename IR>
  mapped_range<V, M, IR> map_range(M mapper, IR input) {
    return mapped_range<V, M, IR>(mapper, input);
  }
}