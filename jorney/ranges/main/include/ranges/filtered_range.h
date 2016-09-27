#pragma once

namespace ranges {
  template <typename V, typename F, typename IR>
  class filtered_range {
  public:
    typedef V value_t;
    typedef F filter_t;
    typedef IR input_range_t;

  public:
    filtered_range(F filter, IR input):
      filter(filter),
      input(input) {
    }

    bool is_open() const {
      if (input.is_open())
        advanceUpToSuitedValue();
      return input.is_open() && filter(input.current());
    }

    value_t current() const {
      advanceUpToSuitedValue();
      return input.current();
    }

    void advance() {
      input.advance();
    }

  private:
    void advanceUpToSuitedValue() const {
      while (input.is_open()) {
        value_t v = input.current();
        if (filter(v))
          return;
        else
          input.advance();
      }
    }

  private:
    filter_t filter;
    mutable input_range_t input;
  };

  template <typename F, typename IR>
  filtered_range<typename IR::value_t, F, IR> filter_range(F filter, IR input) {
    return filtered_range<IR::value_t, F, IR>(filter, input);
  }
}