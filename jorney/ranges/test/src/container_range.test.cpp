#include "gmock/gmock.h"
#include "ranges/container_range.h"
#include <list>
#include <string>
#include <vector>

using namespace ::testing;
using namespace ::ranges;

TEST(ContainerRange, Closed_for_empty_container) {
  auto range = container_range(std::vector<int>());
  ASSERT_THAT(range.is_open(), Eq(false));
}

TEST(ContainerRange, Open_for_container_with_one_element) {
  std::vector<char> chars;
  chars.push_back('a');
  auto range = container_range(chars);
  ASSERT_THAT(range.is_open(), Eq(true));
}

TEST(ContainerRange, Gives_first_element_when_created) {
  auto range = container_range(std::string("a"));
  ASSERT_THAT(range.current(), Eq('a'));
}

TEST(ContainerRange, Geves_next_element_when_advanced) {
  auto range = container_range(std::string("ab"));
  range.advance();
  ASSERT_THAT(range.current(), Eq('b'));
}

TEST(ContainerRange, Closed_when_advanced_over_the_last_element)
{
  auto range = container_range(std::string("a"));
  range.advance();
  ASSERT_THAT(range.is_open(), Eq(false));
}

TEST(ContainerRange, Iterate_through_range)
{
  std::list<char> chars;
  for (auto range = container_range(std::string("abcdef"))
      ; range.is_open(); range.advance())
    chars.push_back(range.current());
  ASSERT_THAT(chars, ElementsAre('a', 'b', 'c', 'd', 'e', 'f'));
}