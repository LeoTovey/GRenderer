//
// Created by leo on 23-6-27.
//


#include "Normal3.h"
#include <gtest/gtest.h>

using namespace GRender;

TEST(Normal3, Basic)
{
    Vector3f vf(1.0, 2.0, -3.0);
    Normal3f n3(1.0, 2.0, -3.0);
    EXPECT_EQ(n3, Normal3f(vf));

}