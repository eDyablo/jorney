#include "gmock/gmock.h"

using namespace ::testing;

TEST(Probe, Success) {
	ASSERT_THAT(0, Eq(0));
}

TEST(Probe, Fail) {
	ASSERT_THAT(0, Eq(1));
}