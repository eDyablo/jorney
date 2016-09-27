#include "closed_range_stub.h"
#include "gmock/gmock.h"
#include "open_range_stub.h"
#include "range_tools.h"
#include "ranges/mapped_range.h"
#include "sequence_range_stub.h"
#include "value_range_stub.h"
#include <functional>
#include <string>
#include <utility>
#include <vector>

using namespace ::testing;
using namespace ::ranges;

auto noMapping = [] () {};

TEST(MappedRange, Open_when_input_range_is_open) {
  auto const range = map_range<void>(noMapping, open_range_stub_t<void>());
  ASSERT_THAT(range.is_open(), Eq(true));
}

TEST(MappedRange, Closed_when_input_range_is_closed) {
  auto const range = map_range<void>(noMapping, closed_range_stub_t<void>());
  ASSERT_THAT(range.is_open(), Eq(false));
}

TEST(MappedRange, Applies_mapper_to_value) {
  bool mapperCalled = false;
  auto const mapper = [&mapperCalled](int) { return mapperCalled = true; };
  auto range = map_range<int>(mapper, open_range_stub_t<int>());
  range.current();
  ASSERT_THAT(mapperCalled, Eq(true));
}

TEST(MappedRange, Gives_range_value) {
  auto const mapper = [] (std::string const&) { return "mapped"; };
  auto const input = value_range_stub_t<std::string>("input");
  auto range = map_range<std::string>(mapper, input);
  ASSERT_THAT(range.current(), Eq("mapped"));
}

TEST(MappedRange, Maps_all_input_values) {
  std::string const words[] = {
      "The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
  auto const mapper = [] (std::string const& word) { return word.size(); };
  auto range = map_range<size_t>(mapper, make_range(words));
  ASSERT_THAT(make_vector(range), ElementsAre(3, 5, 5, 3, 5, 4, 3, 4, 3));
}

TEST(MappedRange, Can_chain_mapped_ranges) {
  std::string const words[] = {"The", "quick", "brown", "fox"};
  size_t counter = 0;
  auto range = map_range<std::pair<size_t, size_t>>(
      [&counter](size_t v) { return std::make_pair(++counter, v); },
      map_range<size_t>(std::mem_fun_ref(&std::string::length),
          make_range(words)));
  ASSERT_THAT(make_vector(range), ElementsAre(
      std::make_pair(1, 3), std::make_pair(2, 5),
      std::make_pair(3, 5), std::make_pair(4, 3)));
}