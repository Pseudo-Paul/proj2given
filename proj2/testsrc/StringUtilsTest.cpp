#ifdef USE_GTEST
#include <gtest/gtest.h>
#include "../include/StringUtils.h"

TEST(StringUtils, EmptyTest) {
    EXPECT_TRUE(true);
}
#else
// Dummy main function to allow compilation without GoogleTest
int main() {
    return 0;
}
#endif
