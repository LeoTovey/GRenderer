//
// Created by leo on 23-6-28.
//

#include <gtest/gtest.h>
#include "Bounds2.h"
#include "Bounds3.h"

using namespace GRender;

TEST(Bounds3, Basics)
{
    Point3f x1(0.0, 0.0, 0.0);
    Point3f x2(0.5, 0.5, 0.5);
    Point3f x3(1.0, 1.0, 1.0);
    Point3f x4(2.0, 2.0, 2.0);
    Bounds3f bf1(x1, x3);
    Bounds3f bf2(x2, x4);
    Bounds3f bf3(x1, x4);

    EXPECT_EQ(x1, bf1[0]);
    EXPECT_EQ(x3, bf1[1]);
    EXPECT_EQ(Union(bf1, x4), Bounds3f(x1, x4));
    EXPECT_EQ(Union(bf1, bf2), Bounds3f(x1, x4));
    EXPECT_EQ(Intersect(bf1, bf2), Bounds3f(x2, x3));

    EXPECT_EQ(Inside(bf1, x2), true);
    EXPECT_EQ(InsideExclusive(bf1, x2), true);
    EXPECT_EQ(InsideExclusive(bf1, x3), false);

    EXPECT_FLOAT_EQ(0.0f, DistanceSquared(bf1, x2));
    EXPECT_FLOAT_EQ(0.0f, DistanceSquared(bf1, x1));
    EXPECT_FLOAT_EQ(0.0f, DistanceSquared(bf1, x3));

    EXPECT_FLOAT_EQ(DistanceSquared(x3, x4), DistanceSquared(bf1, x4));
    EXPECT_FLOAT_EQ(1.0, DistanceSquared(bf1, Point3f(0.5, 0.5, 2.0)));


    EXPECT_FLOAT_EQ(0.0f, Distance(bf1, x2));
    EXPECT_FLOAT_EQ(0.0f, Distance(bf1, x1));
    EXPECT_FLOAT_EQ(0.0f, Distance(bf1, x3));

    EXPECT_FLOAT_EQ(Distance(x3, x4), Distance(bf1, x4));
    EXPECT_FLOAT_EQ(1.0, Distance(bf1, Point3f(0.5, 0.5, 2.0)));

    EXPECT_EQ(bf1, Expand(Bounds3f(x2, x2), 0.5));


    EXPECT_FLOAT_EQ(bf1.Volume(), 1.0f);
    EXPECT_FLOAT_EQ(bf1.SurfaceArea(), 6.0f);

    EXPECT_EQ(Bounds3f({2.0, 1.0, 1.0}, {0.0, 0.0, 0.0}).MaxDimension(), 0);
    EXPECT_EQ(Bounds3f({1.0, 2.0, 1.0}, {0.0, 0.0, 0.0}).MaxDimension(), 1);
    EXPECT_EQ(Bounds3f({1.0, 1.0, 2.0}, {0.0, 0.0, 0.0}).MaxDimension(), 2);

    EXPECT_EQ(Point3f(0.0, 0.5, 1.0), bf1.Lerp(Point3f(0.0, 0.5, 1.0)));
    EXPECT_EQ(Point3f(0.1, 0.2, 1.0), bf1.Lerp(Point3f(0.1, 0.2, 1.0)));

    EXPECT_EQ(Vector3f(0.0, 0.5, 0.25), bf3.Offset(Point3f(0.0, 1.0, 0.5)));
    EXPECT_EQ(Vector3f(0.0, 0.0, 0.0), bf3.Offset(Point3f(0.0, 0.0, 0.0)));
    EXPECT_EQ(Vector3f(1.0, 1.0, 1.0), bf3.Offset(Point3f(2.0, 2.0, 2.0)));

    Point3f center;
    float radius;
    bf3.BoundingSphere(&center, &radius);
    EXPECT_EQ(center, Point3f(1.0, 1.0, 1.0));
    EXPECT_FLOAT_EQ(radius, std::sqrt(3.0));

    Bounds3f bf0(x1);
    bf0.BoundingSphere(&center, &radius);
    EXPECT_EQ(center, x1);
    EXPECT_FLOAT_EQ(radius, 0.0);

    EXPECT_EQ(Bounds3f(x1, x2).IsEmpty(), false);
    EXPECT_EQ(Bounds3f(x1, x1).IsEmpty(), true);

    Bounds3f degenerate_bf;
    degenerate_bf.p_max = x1;
    degenerate_bf.p_min = x3;
    EXPECT_EQ(degenerate_bf.IsDegenerate(), true);
}

TEST(Bounds2, Basics)
{
    Point2f x1(0.0, 0.0);
    Point2f x2(0.5, 0.5);
    Point2f x3(1.0, 1.0);
    Point2f x4(2.0, 2.0);
    Bounds2f bf1(x1, x3);
    Bounds2f bf2(x2, x4);
    Bounds2f bf3(x1, x4);

    EXPECT_EQ(x1, bf1[0]);
    EXPECT_EQ(x3, bf1[1]);
    EXPECT_EQ(Union(bf1, x4), Bounds2f(x1, x4));
    EXPECT_EQ(Union(bf1, bf2), Bounds2f(x1, x4));
    EXPECT_EQ(Intersect(bf1, bf2), Bounds2f(x2, x3));

    EXPECT_EQ(Inside(bf1, x2), true);
    EXPECT_EQ(InsideExclusive(bf1, x2), true);
    EXPECT_EQ(InsideExclusive(bf1, x3), false);

    EXPECT_FLOAT_EQ(0.0f, DistanceSquared(bf1, x2));
    EXPECT_FLOAT_EQ(0.0f, DistanceSquared(bf1, x1));
    EXPECT_FLOAT_EQ(0.0f, DistanceSquared(bf1, x3));

    EXPECT_FLOAT_EQ(DistanceSquared(x3, x4), DistanceSquared(bf1, x4));
    EXPECT_FLOAT_EQ(1.0, DistanceSquared(bf1, Point2f(0.5, 2.0)));


    EXPECT_FLOAT_EQ(0.0f, Distance(bf1, x2));
    EXPECT_FLOAT_EQ(0.0f, Distance(bf1, x1));
    EXPECT_FLOAT_EQ(0.0f, Distance(bf1, x3));

    EXPECT_FLOAT_EQ(Distance(x3, x4), Distance(bf1, x4));
    EXPECT_FLOAT_EQ(1.5, Distance(bf1, Point2f(0.5, 2.5)));

    EXPECT_EQ(bf1, Expand(Bounds2f(x2, x2), 0.5));


    EXPECT_FLOAT_EQ(bf1.Area(), 1.0f);

    EXPECT_EQ(Bounds2f({2.0, 1.0}, {0.0, 0.0}).MaxDimension(), 0);
    EXPECT_EQ(Bounds2f({1.0, 2.0}, {0.0, 0.0}).MaxDimension(), 1);

    EXPECT_EQ(Point2f(0.0, 0.5), bf1.Lerp(Point2f(0.0, 0.5)));
    EXPECT_EQ(Point2f(0.1, 0.2), bf1.Lerp(Point2f(0.1, 0.2)));

    EXPECT_EQ(Vector2f(0.0, 0.5), bf3.Offset(Point2f(0.0, 1.0)));
    EXPECT_EQ(Vector2f(0.0, 0.0), bf3.Offset(Point2f(0.0, 0.0)));
    EXPECT_EQ(Vector2f(1.0, 1.0), bf3.Offset(Point2f(2.0, 2.0)));

    Point2f center;
    float radius;
    bf3.BoundingSphere(&center, &radius);
    EXPECT_EQ(center, Point2f(1.0, 1.0));
    EXPECT_FLOAT_EQ(radius, std::sqrt(2.0));

    Bounds2f bf0(x1);
    bf0.BoundingSphere(&center, &radius);
    EXPECT_EQ(center, x1);
    EXPECT_FLOAT_EQ(radius, 0.0);

    EXPECT_EQ(Bounds2f(x1, x2).IsEmpty(), false);
    EXPECT_EQ(Bounds2f(x1, x1).IsEmpty(), true);

    Bounds2f degenerate_bf;
    degenerate_bf.p_max = x1;
    degenerate_bf.p_min = x3;
    EXPECT_EQ(degenerate_bf.IsDegenerate(), true);
}