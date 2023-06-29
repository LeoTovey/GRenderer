//
// Created by leo on 23-6-27.
//

#ifndef GRENDERER_RAY_H
#define GRENDERER_RAY_H

#include "Point3.h"
#include "Vector3.h"


namespace GRender
{
    class Medium;
    class Ray
    {
    public:

        Point3f operator()(float t) const
        {
            return o + t * d;
        }

        /**
         * /deprecated
         * @param o
         * @param d
         * @param time
         */
        Ray(Point3f o, Vector3f d, float time = 0.f) : o(o), d(d), time(time)
        {

        }

        Point3f o;
        Vector3f d;
        float time = 0.0f;
        //Medium medium = nullptr;
    };
}
#endif //GRENDERER_RAY_H
