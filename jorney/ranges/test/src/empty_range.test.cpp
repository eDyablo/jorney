#include "gmock/gmock.h"
#include "ranges/empty_range.h"
#include "ranges/empty_range_exception.h"

using namespace ::testing;
using namespace ::ranges;

TEST(EmptyRange, Closed) {
  empty_range_t<int> range;
  ASSERT_THAT(range.is_open(), Eq(false));
}

TEST(EmptyRange, Throws_when_asked_for_current_value) {
  empty_range_t<int> range;
  ASSERT_THROW(range.current(), empty_range_exception);
}

TEST(EmptyRange, Does_not_throw_when_advance) {
  empty_range_t<int> range;
  ASSERT_NO_THROW(range.advance());
}