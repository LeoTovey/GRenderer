//
// Created by LeoTovey on 2023/6/24.
//

#include <gtest/gtest.h>

#include "Vector2.h"
#include "Vector3.h"

using namespace GRender;

TEST(Vector2, Basics)
{

    Vector2f vf(-1, 10);
    Vector2d vd(-1, 10);
    EXPECT_EQ(Vector2f(-2, 20), vf + vf);
    EXPECT_EQ(Vector2f(0, 0), vf - vf);
    EXPECT_EQ(Vector2f(-2, 20), vf * 2);
    EXPECT_EQ(Vector2f(-2, 20), 2 * vf);
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

TEST(Vector2, Operations)
{
    EXPECT_EQ(Vector2f(1, 2), Abs(Vector2f (-1, -2)));
    EXPECT_EQ(Vector2f(2.0, 3.0), Ceil(Vector2f(1.2, 2.8)));
    EXPECT_EQ(Vector2f(1.0, 2.0), Floor(Vector2f(1.2, 2.8)));
    EXPECT_EQ(Vector2f(0.0, 0.0), Lerp(0.0f, Vector2f(0.0, 0.0), Vector2f(1.0, 1.0)));
    EXPECT_EQ(Vector2f(0.5, 0.5), Lerp(0.5f, Vector2f(0.0, 0.0), Vector2f(1.0, 1.0)));
    EXPECT_EQ(Vector2f(1.0, 1.0), Lerp(1.0f, Vector2f(0.0, 0.0), Vector2f(1.0, 1.0)));

    EXPECT_EQ(Vector2f(1.0, 1.0), Max(Vector2f(0.0, 1.0), Vector2f(1.0, 0.0)));
    EXPECT_EQ(Vector2f(0.0, 0.0), Min(Vector2f(0.0, 1.0), Vector2f(1.0, 0.0)));

    EXPECT_EQ(0.0, MinComponentValue(Vector2f(0.0, 1.0)));
    EXPECT_EQ(1.0, MaxComponentValue(Vector2f(0.0, 1.0)));
    EXPECT_EQ(0, MinComponentIndex(Vector2f(0.0, 1.0)));
    EXPECT_EQ(1, MaxComponentIndex(Vector2f(0.0, 1.0)));

    EXPECT_EQ(Vector2f(0.0, 1.0), Permute(Vector2f(1.0, 0.0), {1, 0}));
    EXPECT_EQ(HProd(Vector2f(2.0, -1.0)), -2);

    EXPECT_EQ(Vector2f(1.0, 1.0), Vector2f(Vector2d(1.0, 1.0)));

}

TEST(Vector3, Basics)
{


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

TEST(Vector3, Operations)
{
    EXPECT_EQ(Vector3f(1, 2, 0), Abs(Vector3f(-1, -2, 0)));
    EXPECT_EQ(Vector3f(2.0, 3.0, -1.0), Ceil(Vector3f(1.2, 2.8, -1.2)));
    EXPECT_EQ(Vector3f(1.0, 2.0, -4.0), Floor(Vector3f(1.2, 2.8, -3.8)));
    EXPECT_EQ(Vector3f(0.0, 0.0, 0.0), Lerp(0.0f, Vector3f(0.0, 0.0, 0.0), Vector3f(1.0, 1.0, 1.0)));
    EXPECT_EQ(Vector3f(0.5, 0.5, 0.5), Lerp(0.5f, Vector3f(0.0, 0.0, 0.0), Vector3f(1.0, 1.0, 1.0)));
    EXPECT_EQ(Vector3f(1.0, 1.0, 1.0), Lerp(1.0f, Vector3f(0.0, 0.0, 0.0), Vector3f(1.0, 1.0, 1.0)));

    EXPECT_EQ(Vector3f(1.0, 1.0, 2.0), Max(Vector3f(0.0, 1.0, 2.0), Vector3f(1.0, 0.0, -2.0)));
    EXPECT_EQ(Vector3f(0.0, 0.0, -2.0), Min(Vector3f(0.0, 1.0, 2.0), Vector3f(1.0, 0.0, -2.0)));

    EXPECT_EQ(-1.0, MinComponentValue(Vector3f(-1.0, 1.0, 2.0)));
    EXPECT_EQ(2.0, MaxComponentValue(Vector3f(0.0, 1.0, 2.0)));
    EXPECT_EQ(0, MinComponentIndex(Vector3f(0.0, 1.0, 2.0)));
    EXPECT_EQ(2, MaxComponentIndex(Vector3f(0.0, 1.0, 2.0)));

    EXPECT_EQ(Vector3f(0.0, 1.0, -1.0), Permute(Vector3f(1.0, 0.0, -1.0), {1, 0, 2}));
    EXPECT_EQ(HProd(Vector3f(2.0, -1.0, 0.0)), 0);
    EXPECT_EQ(HProd(Vector3f(2.0, -1.0, 1.0)), -2);

    EXPECT_EQ(Vector3f(1.0, 1.0, 1.0), Vector3f(Vector3d(1.0, 1.0, 1.0)));
    EXPECT_EQ(3.0, LengthSquared(Vector3d(1.0, 1.0, 1.0)));
    EXPECT_EQ(5, Length(Vector3d(3.0, 4.0, 0.0)));

    float a = 1.0, b = 2.0, c = -3.0;
    float len = std::sqrt(a * a + b * b + c * c);
    for (int i = 0; i < 3; ++i) {
        EXPECT_FLOAT_EQ(Vector3(a / len, b / len, c / len)[i], Normalize(Vector3d(a, b, c))[i]);
    }


    Vector3f v1(1.0, 2.0, 4.0);
    Vector3f v2(0.0, -1.0, 1.0);
    EXPECT_EQ(2.0, Dot(v1, v2));
    EXPECT_EQ(1.0, AbsDot(Vector3f(1.0, 2.0, 4.0), Vector3f(-1.0, 2.0, -1.0)));
    EXPECT_FLOAT_EQ(Pi * 0.5, AngleBetween(Vector3f(1.0, 0.0, 0.0), Vector3f(0.0, 1.0, 0.0)));
}