#include "gmock/gmock.h"
#include "range_tools.h"
#include "ranges/filtered_range.h"
#include "ranges/mapped_range.h"
#include "sequence_range_stub.h"
#include <functional>
#include <string>
#include <vector>

using namespace ::testing;
using namespace ::ranges;

TEST(MapAndFilter, Can_map_filtered_range_that_has_values) {
  const std::string words[] = {
      "The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
  const auto filter = [] (const std::string& s) {
    return s.find('o') != std::string::npos; };
  auto range = map_range<size_t>(std::mem_fun_ref(&std::string::length),
      filter_range(filter, make_range(words)));
  ASSERT_THAT(make_vector(range), ElementsAre(5, 3, 4, 3));
}

TEST(MapAndFilter, Can_filter_mapped_range_that_has_values) {
  const std::string words[] = {
      "The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
  auto range = filter_range(std::bind2nd(std::greater<size_t>(), 3),
      map_range<size_t>(std::mem_fun_ref(&std::string::length),
          make_range(words)));
  ASSERT_THAT(make_vector(range), ElementsAre(5, 5, 5, 4, 4));
}

TEST(MapAndFilter, Can_map_filtered_range_that_has_no_values) {
  const std::string words[] = {"The", "quick", "brown", "fox"};
  auto range = map_range<size_t>(std::mem_fun_ref(&std::string::length),
      filter_range([](const std::string&) { return false; },
      make_range(words)));
  ASSERT_THAT(make_vector(range), IsEmpty());
}