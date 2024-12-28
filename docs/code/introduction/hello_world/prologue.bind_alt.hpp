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

using L = mp_list<Arg_0, Arg_1, Arg_2>;

template<typename...Args>
using BindAlt = mp_compose
<
    mp_bind_front<mp_list, Arg_0, Arg_1>::fn,
    mp_bind_back<mp_fold_q, V, Subtract>::fn
>
::fn<Args...>;

static_assert(std::same_as<
    BindAlt<Arg_2>,
    mp_fold_q<L, V, Subtract>
>);

using Arg_3 = mp_value<2>;

using L_1 = mp_list<Arg_0, Arg_1, Arg_2, Arg_3>;

static_assert(std::same_as<
    BindAlt<Arg_2, Arg_3>,
    mp_fold_q<L_1, V, Subtract>
>);