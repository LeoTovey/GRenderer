//
// Created by LeoTovey on 2023/6/24.
//

#include <gtest/gtest.h>

#include "Vector2.h"
#include "Vector3.h"

using namespace GRender;
TEST(Vector2, Basics)
{
    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;
    using Vector2i = Vector2<int>;
    using Vector2u = Vector2<unsigned int>;

    Vector2f vf(-1, 10);
    Vector2d vd(-1, 10);
    EXPECT_EQ(Vector2f(-2, 20), vf + vf);
    EXPECT_EQ(Vector2f(0, 0), vf - vf);
    EXPECT_EQ(Vector2f(-2, 20), vf * 2);
    EXPECT_EQ(Vector2f(-0.5, 5), vf / 2);
    ASSERT_DEATH(vf / 0, "");

    EXPECT_EQ(Vector2f(-2, 20), vf + vd);
    EXPECT_EQ(Vector2f(0, 0), vf - vd);


    EXPECT_EQ(Vector2f(-2, 20), vf += vd);
    EXPECT_EQ(Vector2f(-1, 10), vf -= vd);
    EXPECT_EQ(Vector2f(-2, 20), vf *= 2);
    EXPECT_EQ(Vector2f(-1, 10), vf /= 2);
    ASSERT_DEATH(vf /= 0, "");

    EXPECT_EQ(Vector2f(1, -10), -vf);
    EXPECT_EQ(-1, vf[0]);
    vf[0] = 10;
    EXPECT_EQ(10, vf[0]);

    std::cout << vf.ToString() << std::endl;
    ASSERT_DEATH(vf * std::nan("123"), "");

    EXPECT_EQ(vf, Vector2f(vf));
    EXPECT_EQ(vf, vf = Vector2f(-1, 10));
}

TEST(Vector3, Basics)
{
    using Vector3f = Vector3<float>;
    using Vector3d = Vector3<double>;
    using Vector3i = Vector3<int>;
    using Vector3u = Vector3<unsigned int>;

    Vector3f vf(-1, 10, -3);
    Vector3d vd(-1, 10, 0);

    EXPECT_EQ(Vector3f(-2, 20, -6), vf + vf);
    EXPECT_EQ(Vector3f(0, 0, 0), vf - vf);
    EXPECT_EQ(Vector3f(-2, 20, -6), vf * 2);
    EXPECT_EQ(Vector3f(-0.5, 5, -1.5), vf / 2);
    ASSERT_DEATH(vf / 0, "");

    EXPECT_EQ(Vector3f(-2, 20, -3), vf + vd);
    EXPECT_EQ(Vector3f(0, 0, -3), vf - vd);

    EXPECT_EQ(Vector3f(-2, 20, -3), vf += vd);
    EXPECT_EQ(Vector3f(-1, 10, -3), vf -= vd);
    EXPECT_EQ(Vector3f(-2, 20, -6), vf *= 2);
    EXPECT_EQ(Vector3f(-1, 10, -3), vf /= 2);
    ASSERT_DEATH(vf /= 0, "");

    EXPECT_EQ(Vector3f(1, -10, 3), -vf);
    EXPECT_EQ(-1, vf[0]);
    vf[0] = 10;
    EXPECT_EQ(10, vf[0]);

    std::cout << vf.ToString() << std::endl;
    ASSERT_DEATH(vf * std::nan("123"), "");

    EXPECT_EQ(vf, Vector3f(vf));
    EXPECT_EQ(vf, vf = Vector3f(-1, 10, -3));
}