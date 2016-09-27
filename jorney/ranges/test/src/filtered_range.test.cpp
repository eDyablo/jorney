#include "closed_range_stub.h"
#include "gmock/gmock.h"
#include "open_range_stub.h"
#include "range_tools.h"
#include "ranges/filtered_range.h"
#include "sequence_range_stub.h"
#include "value_range_stub.h"
#include <functional>
#include <string>
#include <vector>

using namespace ::testing;
using namespace ::ranges;

auto allowAllFilter = [] (int) { return true; };

TEST(FilteredRange, Open_when_input_range_is_open) {
  auto range = filter_range(allowAllFilter, open_range_stub_t<int>());
  ASSERT_THAT(range.is_open(), Eq(true));
}

TEST(FilteredRange, Closed_when_input_range_is_closed) {
  auto range = filter_range(allowAllFilter, closed_range_stub_t<int>());
  ASSERT_THAT(range.is_open(), Eq(false));
}

TEST(FilteredRange, Calls_filter_when_asked_for_current_value) {
  bool filterCalled = false;
  auto const filter = [&filterCalled] (int) -> bool {
    filterCalled = true;
    return true;
  };
  auto range = filter_range(filter, open_range_stub_t<int>());
  range.current();
  ASSERT_THAT(filterCalled, Eq(true));
}

TEST(FilteredRange, Returns_value_that_meets_filter_criterion) {
  int const sequence[] = {1, 2, 3, 4};
  auto const filter = [] (int value) {  return value == 2; };
  auto range = filter_range(filter, make_range(sequence));
  ASSERT_THAT(range.current(), Eq(2));
}

TEST(FilteredRange, Closed_when_input_has_no_value_that_meets_filter_criterion) {
  int const sequence[] = {1, 2, 3};
  auto const filter = [] (int v) { return v > 3; };
  auto range = filter_range(filter, make_range(sequence));
  ASSERT_THAT(range.is_open(), Eq(false));
}

TEST(FilteredRange, Open_when_input_has_value_that_meets_filter_criterion) {
  int const sequence[] = {1, 2, 3};
  auto const filter = [] (int v) { return v == 2; };
  auto range = filter_range(filter, make_range(sequence));
  ASSERT_THAT(range.is_open(), Eq(true));
}

TEST(FilteredRange, Returns_all_values_that_meets_filter_criterion) {
  int const sequence[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  auto const filter = [] (int v) { return v % 3 == 0; };
  auto range = filter_range(filter, make_range(sequence));
  ASSERT_THAT(make_vector(range), ElementsAre(3, 6, 9));
}

TEST(FilteredRange, Can_chain_filtered_ranges) {
  int const numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  auto range = filter_range([] (int v) { return v % 2 == 0; },
      filter_range(std::bind2nd(std::greater<int>(), 6),
          make_range(numbers)));
  ASSERT_THAT(make_vector(range), ElementsAre(8, 10, 12));
}