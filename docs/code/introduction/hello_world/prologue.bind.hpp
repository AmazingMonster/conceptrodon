#include "boost/mp11.hpp"

using namespace boost;
using namespace mp11;

struct Subtract
{
    template<typename A, typename B>
    using fn = mp_value<A::value - B::value>;
};

using V = mp_value<1>;

using Arg_0 = mp_value<3>;
using Arg_1 = mp_value<4>;
using Arg_2 = mp_value<3>;

using L = mp_list<mp_value<3>, mp_value<4>, mp_value<3>>;

template<typename...Args>
using Bind = mp_bind
<
    mp_fold_q,
    mp_bind<mp_list, Arg_0, Arg_1, _3>,
    _1,
    _2
>
::fn<Args...>;

static_assert(std::same_as<
    Bind<V, Subtract, Arg_2>,
    mp_fold_q<L, V, Subtract>
>);