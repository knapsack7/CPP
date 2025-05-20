#include <gtest/gtest.h>
#include "board.h"

TEST(BoardTest, SingletonInstance) {
    auto& instance1 = Board::getInstance();
    EXPECT_THROW(Board::getInstance(), std::runtime_error);  // Should throw on second call
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// Add more tests as needed