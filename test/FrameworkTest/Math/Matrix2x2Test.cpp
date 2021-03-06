// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#include <Pomdog/Math/Matrix2x2.hpp>
#include <gtest/iutest_switch.hpp>

using Pomdog::Matrix2x2;

namespace {

static constexpr auto Epsilon = std::numeric_limits<float>::epsilon();

}// unused namespace

TEST(Matrix2x2, FirstTestCase)
{
    Matrix2x2 matrix{1.0f, 1.0f, 1.0f, 1.0f};
    EXPECT_EQ(1.0f, matrix(0, 0));
    EXPECT_EQ(1.0f, matrix(0, 1));
    EXPECT_EQ(1.0f, matrix(1, 0));
    EXPECT_EQ(1.0f, matrix(1, 1));

    matrix = Matrix2x2{0.0f, 1.0f, 2.0f, 3.0f};
    EXPECT_EQ(0.0f, matrix(0, 0));
    EXPECT_EQ(1.0f, matrix(0, 1));
    EXPECT_EQ(2.0f, matrix(1, 0));
    EXPECT_EQ(3.0f, matrix(1, 1));
}

TEST(Matrix2x2, Identity)
{
    EXPECT_EQ(1.0f, Matrix2x2::Identity(0, 0));
    EXPECT_EQ(0.0f, Matrix2x2::Identity(0, 1));
    EXPECT_EQ(0.0f, Matrix2x2::Identity(1, 0));
    EXPECT_EQ(1.0f, Matrix2x2::Identity(1, 1));

    Matrix2x2 matrix = Matrix2x2::Identity;
    EXPECT_EQ(1.0f, matrix(0, 0));
    EXPECT_EQ(0.0f, matrix(0, 1));
    EXPECT_EQ(0.0f, matrix(1, 0));
    EXPECT_EQ(1.0f, matrix(1, 1));
}
