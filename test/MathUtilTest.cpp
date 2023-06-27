//
// Created by leo on 23-6-25.
//

#include <gtest/gtest.h>

#include "MathUtil.h"


TEST(MathUtil, FMA)
{
    std::cout<<FMA(1, 2, 3);
    //std::cout<<FMA(1.0, 2.0, 3.0);

    EXPECT_EQ(4, Sqr(2));
}
