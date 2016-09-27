#include "ranges/single_value_range.h"
#include "gmock/gmock.h"

using namespace ::testing;
using namespace ::ranges;

TEST(SingleValueRange, Open_when_created) {
  auto const range = value_range(0);
  ASSERT_THAT(range.is_open(), Eq(true));
}

TEST(SingleValueRange, Gives_the_value) {
  auto const range = value_range(1);
  ASSERT_THAT(range.current(), Eq(1));
}

TEST(SingleValueRange, Closed_after_advance) {
  auto range = value_range(0);
  range.advance();
  ASSERT_THAT(range.is_open(), Eq(false));
}

TEST(SingleValueRange, Gives_the_value_when_advanced) {
  auto range = value_range(1);
  range.advance();
  ASSERT_THAT(range.current(), Eq(1));
}