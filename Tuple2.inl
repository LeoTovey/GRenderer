
#include "Tuple2.h"

namespace GRender
{
    template <template <typename> class Child, typename T>
    Tuple2<Child, T>::Tuple2(T x, T y) : x(x), y(y)
    {

    }

}