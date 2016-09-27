#include "gmock/gmock.h"
#include "ranges/incrementing_range.h"

using namespace ::testing;
using namespace ::ranges;

TEST(IncrementingRange, Is_open_when_created) {
  incrementing_range_t<int> range(1);
  ASSERT_THAT(range.is_open(), Eq(true));
}

TEST(IncrementingRange, Gives_start_value_when_created) {
  incrementing_range_t<int> range(1);
  ASSERT_THAT(range.current(), Eq(1));
}

TEST(IncrementingRange, Gives_next_value_when_advanced) {
  incrementing_range_t<int> range(1);
  range.advance();
  ASSERT_THAT(range.current(), Eq(2));
}