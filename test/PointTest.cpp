//
// Created by leo on 23-6-27.
//

#include "Point3.h"
#include "Point2.h"

#include <gtest/gtest.h>

using namespace GRender;

TEST(Point3, Basic)
{
    Vector3f vf(1.0, 2.0, -3.0);
    EXPECT_EQ(Point3f(1.0, 2.0, -3.0), Point3f(vf));
    EXPECT_EQ(Point3f(1.0, 2.0, -3.0), Point3i(vf));
    EXPECT_EQ(Vector3f(1.0, 2.0, -3.0), Vector3f(Point3f(1.0, 2.0, -3.0)));

    EXPECT_EQ(Point3f(1.0, 1.0, 1.0), Point3f(0.0, 0.0, 0.0) + Vector3f(1.0, 1.0, 1.0));
    EXPECT_EQ(Vector3f(0.0, 0.0, 0.0), Point3f(1.0, 1.0, 1.0) - Point3f (1.0, 1.0, 1.0));
    EXPECT_EQ(Point3f(0.0, 0.0, 0.0), Point3f(1.0, 1.0, 1.0) - Vector3f(1.0, 1.0, 1.0));

    EXPECT_EQ(3.0, DistanceSquared(Point3f(1.0, 1.0, 1.0), Point3f(0.0, 0.0, 0.0)));
    EXPECT_EQ(5, Distance(Point3f (3.0, 4.0, 0.0), Point3f(0.0, 0.0, 0.0)));

}

TEST(Point2, Basic)
{
    Vector2f vf(1.0, -3.0);
    EXPECT_EQ(Point2f(1.0, -3.0), Point2f(vf));
    EXPECT_EQ(Point2f(1.0, -3.0), Point2i(vf));
    EXPECT_EQ(Vector2f(1.0, -3.0), Vector2f(Point2f(1.0, -3.0)));

    EXPECT_EQ(Point2f(1.0, 1.0), Point2f(0.0, 0.0) + Vector2f(1.0, 1.0));
    EXPECT_EQ(Vector2f(0.0, 0.0), Point2f(1.0, 1.0) - Point2f (1.0, 1.0));
    EXPECT_EQ(Point2f (0.0, 0.0), Point2f(1.0, 1.0) - Vector2f(1.0, 1.0));

    EXPECT_EQ(2.0, DistanceSquared(Point2f(1.0, 1.0), Point2f(0.0, 0.0)));
    EXPECT_EQ(5, Distance(Point2f (3.0, 4.0), Point2f(0.0, 0.0)));
}